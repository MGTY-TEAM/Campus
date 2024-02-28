// Fill out your copyright notice in the Description page of Project Settings.


#include "Campus/AI/Tasks/DefineActionTask.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Campus/AI/AIDrone/CoreDrone/AIAnimDrone.h"
#include "Campus/AI/AIDroneController.h"

UDefineActionTask::UDefineActionTask()
{
	NodeName = "Define Action";
}

EBTNodeResult::Type UDefineActionTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* const Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Blackboard) return EBTNodeResult::Failed;

	AAIController* const Controller = OwnerComp.GetAIOwner();
	if (!Controller) return EBTNodeResult::Failed;

	Controller->ClearFocus(EAIFocusPriority::Default);

	// AAIAnimDrone* const Drone = Cast<AAIAnimDrone>(Controller->GetPawn());
	// if (!Drone) return EBTNodeResult::Failed;
	
	Blackboard->SetValueAsEnum(ActionTypeKey.SelectedKeyName, static_cast<uint8>(ActionType));
	// Blackboard->SetValueAsVector(StartLocationKey.SelectedKeyName, Drone->GetStartLocation());
	// Blackboard->SetValueAsBool(BoolNotTheFirstKey.SelectedKeyName, false);

	return EBTNodeResult::Succeeded;
}
