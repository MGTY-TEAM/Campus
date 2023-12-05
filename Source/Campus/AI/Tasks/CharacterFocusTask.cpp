// Fill out your copyright notice in the Description page of Project Settings.


#include "Campus/AI/Tasks/CharacterFocusTask.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Campus/AI/AIDroneController.h"
#include "Campus/Core/BaseCharacter/BaseFirstPersonCharacter.h"

UCharacterFocusTask::UCharacterFocusTask()
{
	NodeName = "Focus On Character";
}

EBTNodeResult::Type UCharacterFocusTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Blackboard) return EBTNodeResult::Failed;

	AAIDroneController* const Controller = Cast<AAIDroneController>(OwnerComp.GetAIOwner());
	if (!Controller) return EBTNodeResult::Failed;

	ABaseFirstPersonCharacter* Character = Cast<ABaseFirstPersonCharacter>(Blackboard->GetValueAsObject(CharacterActorKey.SelectedKeyName));
	if (!Character) return EBTNodeResult::Failed;
		
	if (Character) Controller->SetFocus(Character);
		
	return EBTNodeResult::Succeeded;
}


