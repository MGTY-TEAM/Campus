// Fill out your copyright notice in the Description page of Project Settings.


#include "Campus/AI/Tasks/FindCharacterTask.h"
#include "Campus/AI/AIDroneController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationData.h"
#include "NavigationSystem.h"
#include "AI/Navigation/NavAgentInterface.h"
#include "Campus/AI/AIDrone/CoreDrone/AIAnimDrone.h"
#include "Engine/Engine.h"

UFindCharacterTask::UFindCharacterTask()
{
	NodeName = "Find Character";
	bNotifyTick = true;
}

EBTNodeResult::Type UFindCharacterTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return RequestMove(OwnerComp, NodeMemory);
}

void UFindCharacterTask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if (!IsMoving())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, "ggg");
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
		
	AAIDroneController* const Controller = Cast<AAIDroneController>(OwnerComp.GetAIOwner());
	if (!Controller) return;

	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Blackboard) return;

	bool ISeeYou = Blackboard->GetValueAsBool(ISeeYouKey.SelectedKeyName);
	if (ISeeYou)
	{
		AbortMove(OwnerComp, NodeMemory);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

void UFindCharacterTask::FinishMove(const FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	IsMove = false;
}

EBTNodeResult::Type UFindCharacterTask::RequestMove(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIDroneController* const Controller = Cast<AAIDroneController>(OwnerComp.GetAIOwner());
	if (!Controller) return EBTNodeResult::Failed;

	const UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Blackboard) return EBTNodeResult::Failed;

	FVector DestinationPoint = Blackboard->GetValueAsVector(LastLocationKey.SelectedKeyName);

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
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, MainRequestID.ToString());
	IsMove = true;

	// Controller->GetPathFollowingComponent()->OnRequestFinished.AddUObject(this, &UFindCharacterTask::FinishMove);

	return EBTNodeResult::InProgress;
}

void UFindCharacterTask::AbortMove(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIDroneController* const Controller = Cast<AAIDroneController>(OwnerComp.GetAIOwner());
	if (!Controller) return;

	Controller->GetPathFollowingComponent()->AbortMove(
		*OwnerComp.GetOwner(),
		FPathFollowingResultFlags::MovementStop,
		MainRequestID);
}

ANavigationData* UFindCharacterTask::FindNavigationData(UNavigationSystemV1& NavSys, UObject* Owner) const
{
	INavAgentInterface* NavAgent = Cast<INavAgentInterface>(Owner);
	if (NavAgent)
	{
		return NavSys.GetNavDataForProps(NavAgent->GetNavAgentPropertiesRef(), NavAgent->GetNavAgentLocation());
	}

	return NavSys.GetDefaultNavDataInstance(FNavigationSystem::DontCreate);
}