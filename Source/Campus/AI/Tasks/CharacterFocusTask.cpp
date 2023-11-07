// Fill out your copyright notice in the Description page of Project Settings.


#include "Campus/AI/Tasks/CharacterFocusTask.h"
#include "Campus/AI/AIDrone/CoreDrone/AIAnimDrone.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Campus/AI/AIDroneController.h"
#include "Engine/Engine.h"

UCharacterFocusTask::UCharacterFocusTask()
{
	NodeName = "Focus On Character";
}

EBTNodeResult::Type UCharacterFocusTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Blackboard) return EBTNodeResult::Failed;

	AAIAnimDrone* Drone = Cast<AAIAnimDrone>(Blackboard->GetValueAsObject(CharacterActorKey.SelectedKeyName));
	if (!Drone) return EBTNodeResult::Failed;
		
	if (Drone->DoesHeInteract()) Drone->StartRotateToPlayerAnim();
		
	return EBTNodeResult::Succeeded;
}


