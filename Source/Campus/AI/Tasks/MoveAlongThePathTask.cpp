// Fill out your copyright notice in the Description page of Project Settings.

#include "Campus/AI/Tasks/MoveAlongThePathTask.h"
#include "NavigationData.h"
#include "NavigationSystem.h"
#include "Campus/AI/AIDroneController.h"
#include "AI/Navigation/NavigationTypes.h"
#include "AI/Navigation/NavAgentInterface.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Campus/AI/AIDrone/CampusCoreTypes.h"
#include "Campus/AI/Tasks/CharacterFocusTask.h"
#include "Campus/AI/AIDrone/CoreDrone/AIAnimDrone.h"

UMoveAlongThePathTask::UMoveAlongThePathTask()
{
	NodeName = "Move Along The Path";
	bNotifyTick = true;
}

EBTNodeResult::Type UMoveAlongThePathTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	MyOwnerComp = &OwnerComp;
	return RequestMove(OwnerComp, NodeMemory);
}

void UMoveAlongThePathTask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if (!IsMoving())
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

	const UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Blackboard) return;

	const bool ISeeYou = Blackboard->GetValueAsBool(ISeeYouKey.SelectedKeyName);
	const bool HeIsStandingNow = Blackboard->GetValueAsBool(IsHeStandingKey.SelectedKeyName);
	const bool IsThereObstacle = Blackboard->GetValueAsBool(IsThereObstacleKey.SelectedKeyName);

	const bool CanStop = CheckCapabilityOfStopping();
	
	if ((!ISeeYou || IsThereObstacle) && CanStop)
	{
		ClearTimer();
		PauseMove(OwnerComp, NodeMemory);
	}
	else if (ISeeYou && !IsThereObstacle || !CanStop)
	{
		if (GetWorld() && !SetTimer)
		{
			GetWorld()->GetTimerManager().SetTimer(RequestMoveHandle, this, &UMoveAlongThePathTask::OnRequsetMove,0.25f, false);
			SetTimer = true;
		}
	}

	if (HeIsStandingNow && CanStop)
	{
		ClearTimer();
	}
}

ANavigationData* UMoveAlongThePathTask::FindNavigationData(UNavigationSystemV1& NavSys, UObject* Owner) const
{
	if (const INavAgentInterface* NavAgent = Cast<INavAgentInterface>(Owner))
	{
		return NavSys.GetNavDataForProps(NavAgent->GetNavAgentPropertiesRef(), NavAgent->GetNavAgentLocation());
	}

	return NavSys.GetDefaultNavDataInstance(FNavigationSystem::DontCreate);
}

void UMoveAlongThePathTask::FinishMove(const FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	if (Result.IsSuccess() && RequestID == MainRequestID)
	{
		IsMove = false;

		UBlackboardComponent* Blackboard = MyOwnerComp->GetBlackboardComponent();
		if (!Blackboard) return;

		if (AAIController* Controller = MyOwnerComp->GetAIOwner())
		{
			if (AActor* Character = Cast<AActor>(Blackboard->GetValueAsObject(CharacterActorKey.SelectedKeyName)))
			{
				Controller->SetFocus(Character);
			}
		}

		Blackboard->SetValueAsEnum(ActionTypeKey.SelectedKeyName, static_cast<uint8>(EActionType::Holding));
	}
}

void UMoveAlongThePathTask::ClearTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(RequestMoveHandle);
	SetTimer = false;
}

void UMoveAlongThePathTask::OnRequsetMove()
{
	RequestMove(*MyOwnerComp, nullptr);
}

EBTNodeResult::Type UMoveAlongThePathTask::RequestMove(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	PathPoints.Reset();

	AAIDroneController* const Controller = Cast<AAIDroneController>(OwnerComp.GetAIOwner());
	if (!Controller) return EBTNodeResult::Failed;

	const UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Blackboard) return EBTNodeResult::Failed;

	FVector DestinationPoint = Blackboard->GetValueAsVector(DestinationPointKey.SelectedKeyName);

	AAIAnimDrone* Drone = Cast<AAIAnimDrone>(Blackboard->GetValueAsObject(SelfActorKey.SelectedKeyName));
	if (!Drone) return EBTNodeResult::Failed;

	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(OwnerComp.GetWorld());
	if (!NavSys) return EBTNodeResult::Failed;

	ANavigationData* NavData = FindNavigationData(*NavSys, OwnerComp.GetOwner());
	if (!NavData) return EBTNodeResult::Failed;

	EPathFindingMode::Type PFMode(EPathFindingMode::Hierarchical);
	FSharedConstNavQueryFilter NavFilter = UNavigationQueryFilter::GetQueryFilter(
		*NavData, OwnerComp.GetOwner(), FilterClass);

	FPathFindingQuery Query(OwnerComp.GetOwner(), *NavData, Drone->GetActorLocation(), DestinationPoint, NavFilter);
	Query.SetAllowPartialPaths(false);
	Query.SetNavAgentProperties(15.f);

	FPathFindingResult Result = NavSys->FindPathSync(Query, PFMode);

	FAIMoveRequest MoveRequest(DestinationPoint);
	MainRequestID = Controller->GetPathFollowingComponent()->RequestMove(MoveRequest, Result.Path);

	IsMove = true;

	Controller->ClearFocus(EAIFocusPriority::Gameplay);
	Controller->GetPathFollowingComponent()->OnRequestFinished.AddUObject(this, &UMoveAlongThePathTask::FinishMove);

	if (MainRequestID.IsValid())
	{
		FillNavPoints(Result.Path->GetPathPoints());
	}

	return EBTNodeResult::InProgress;
}

void UMoveAlongThePathTask::PauseMove(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const AAIDroneController* Controller = Cast<AAIDroneController>(OwnerComp.GetAIOwner());
	if (!Controller) return;

	Controller->GetPathFollowingComponent()->PauseMove(MainRequestID);
}

bool UMoveAlongThePathTask::CheckCapabilityOfStopping()
{
	const UBlackboardComponent* Blackboard = MyOwnerComp->GetBlackboardComponent();
	if (!Blackboard) return false;

	const AActor* Drone = Cast<AActor>(Blackboard->GetValueAsObject(SelfActorKey.SelectedKeyName));
	const AActor* Character = Cast<AActor>(Blackboard->GetValueAsObject(CharacterActorKey.SelectedKeyName));
	if (!Drone || !Character) return false;

	FVector ClosestToDrone(TNumericLimits<float>::Max());
	FVector ClosestToCharacter(TNumericLimits<float>::Max());

	for (auto Point : PathPoints)
	{
		float Distance = (Drone->GetActorLocation() - Point).Length();
		float CurrentDistance = (Drone->GetActorLocation() - ClosestToDrone).Length();
		if (Distance < CurrentDistance)
		{
			ClosestToDrone = Point;
		}

		Distance = (Character->GetActorLocation() - Point).Length();
		CurrentDistance = (Character->GetActorLocation() - ClosestToCharacter).Length();
		if (Distance < CurrentDistance)
		{
			ClosestToCharacter = Point;
		}
	}

	const int32 DronePointIndex = PathPoints.IndexOfByKey(ClosestToDrone);
	int32 CharacterPointIndex = PathPoints.IndexOfByKey(ClosestToCharacter);

	if (DronePointIndex != INDEX_NONE && CharacterPointIndex != INDEX_NONE)
	{
		if (CharacterPointIndex < DronePointIndex) CharacterPointIndex = DronePointIndex;

		if (DronePointIndex == CharacterPointIndex)
		{
			if (PathPoints.IsValidIndex(DronePointIndex + 1))
			{
				const FVector NextPoint = PathPoints[DronePointIndex + 1];

				if ((Drone->GetActorLocation() - NextPoint).Length() <= (Character->GetActorLocation() - NextPoint).Length())
				{
					return true;
				}
			}
			return false;
		}
		if (CharacterPointIndex > DronePointIndex)
		{
			return false;
		}
	}
	return false;
}

void UMoveAlongThePathTask::FillNavPoints(const TArray<FNavPathPoint>& Points)
{
	for (auto PathPoint : Points)
	{
		FVector Pos = PathPoint;
		PathPoints.Add(Pos);
	}
}
