// Fill out your copyright notice in the Description page of Project Settings.


#include "Campus/AI/Tasks/TakePickupTask.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Campus/AI/AIDrone/CoreDrone/AIAnimDrone.h"
#include "Campus/Pickups/Garbage/BaseGarbage.h"

UTakePickupTask::UTakePickupTask()
{
	NodeName = "Take pickup";
}

EBTNodeResult::Type UTakePickupTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Blackboard) EBTNodeResult::Failed;

	AAIAnimDrone* Drone = Cast<AAIAnimDrone>(Blackboard->GetValueAsObject(DroneActorKey.SelectedKeyName));
	if (!Drone) return EBTNodeResult::Failed;

	ABaseGarbage* Pickup = Cast<ABaseGarbage>(Blackboard->GetValueAsObject(PickupActorKey.SelectedKeyName));
	if (!Drone) return EBTNodeResult::Failed;

	Pickup->TakingItem(Drone->GetSceneComponent());

	return EBTNodeResult::Succeeded;
}
