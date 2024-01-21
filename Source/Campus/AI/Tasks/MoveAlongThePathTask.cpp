// Fill out your copyright notice in the Description page of Project Settings.

#include "Campus/AI/Tasks/MoveAlongThePathTask.h"
#include "Campus/AI/AIDroneController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationData.h"
#include "NavigationSystem.h"
#include "AI/Navigation/NavAgentInterface.h"
#include "Campus/AI/AIDrone/CoreDrone/AIAnimDrone.h"
#include "Campus/Core/CharacterSystem/BaseCharacter.h"
#include "Engine/Engine.h"

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

	AAIDroneController* const Controller = Cast<AAIDroneController>(OwnerComp.GetAIOwner());
	if (!Controller) return;

	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Blackboard) return;

	// ABaseFirstPersonCharacter* Character = Cast<ABaseFirstPersonCharacter>(Blackboard->GetValueAsObject(CharacterActorKey.SelectedKeyName));
	// if (!Character) return;

	bool ISeeYou = Blackboard->GetValueAsBool(ISeeYouKey.SelectedKeyName);
	if (!ISeeYou && !CharacterIsGone)
	{
		AbortMove(OwnerComp, NodeMemory);
		CharacterIsGone = true;
	}
	else if (ISeeYou && CharacterIsGone)
	{
		RequestMove(OwnerComp, NodeMemory);
		CharacterIsGone = false;
	}
}

ANavigationData* UMoveAlongThePathTask::FindNavigationData(UNavigationSystemV1& NavSys, UObject* Owner) const
{
	INavAgentInterface* NavAgent = Cast<INavAgentInterface>(Owner);
	if (NavAgent)
	{
		return NavSys.GetNavDataForProps(NavAgent->GetNavAgentPropertiesRef(), NavAgent->GetNavAgentLocation());
	}

	return NavSys.GetDefaultNavDataInstance(FNavigationSystem::DontCreate);
}

void UMoveAlongThePathTask::FinishMove(const FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	// if (Result.IsInterrupted()) return;
	// else if (RequestID == MainRequestID) IsMove = false;
	if (Result.IsSuccess() && RequestID == MainRequestID)
	{
		/*IsMove = false;

		UBlackboardComponent* Blackboard = MyOwnerComp->GetBlackboardComponent();
		if (!Blackboard) return;

		ABaseCharacter* Character = Cast<ABaseCharacter>(Blackboard->GetValueAsObject(CharacterActorKey.SelectedKeyName));
		if (!Character) return;

		Character->SetArrivalValue(true);*/
	}
}

EBTNodeResult::Type UMoveAlongThePathTask::RequestMove(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
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

	EPathFindingMode::Type PFMode(EPathFindingMode::Regular);
	FSharedConstNavQueryFilter NavFilter = UNavigationQueryFilter::GetQueryFilter(*NavData, OwnerComp.GetOwner(), FilterClass);

	FPathFindingQuery Query(OwnerComp.GetOwner(), *NavData, Drone->GetActorLocation(), DestinationPoint, NavFilter);
	Query.SetAllowPartialPaths(false);

	FPathFindingResult Result = NavSys->FindPathSync(Query, PFMode);

	FAIMoveRequest MoveRequest(DestinationPoint);
	MainRequestID = Controller->GetPathFollowingComponent()->RequestMove(MoveRequest, Result.Path);
	
	IsMove = true;

	Controller->GetPathFollowingComponent()->OnRequestFinished.AddUObject(this, &UMoveAlongThePathTask::FinishMove);

	return EBTNodeResult::InProgress;
}

void UMoveAlongThePathTask::AbortMove(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIDroneController* const Controller = Cast<AAIDroneController>(OwnerComp.GetAIOwner());
	if (!Controller) return;

	Controller->GetPathFollowingComponent()->AbortMove(
		*OwnerComp.GetOwner(), 
		FPathFollowingResultFlags::MovementStop, 
		MainRequestID);
}
