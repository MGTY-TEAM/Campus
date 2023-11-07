// Fill out your copyright notice in the Description page of Project Settings.


#include "Campus/AI/Services/CharacterIdentificationService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Campus/AI/AIDrone/CoreDrone/AIAnimDrone.h"

UCharacterIdentificationService::UCharacterIdentificationService()
{
	NodeName = "Character Identification";
}

void UCharacterIdentificationService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const AAIController* Controller = OwnerComp.GetAIOwner();
	AAIAnimDrone* Drone = Cast<AAIAnimDrone>(Controller->GetPawn());
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();

	if (Drone && Drone->DoesHeInteract())
	{
		Blackboard->SetValueAsObject(CharacterActorKey.SelectedKeyName, Drone->GetInteractingCharacter());
	}
	else if (Drone && !Drone->DoesHeInteract())
	{
		Blackboard->ClearValue(CharacterActorKey.SelectedKeyName);
	}
	
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
