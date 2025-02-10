// Fill out your copyright notice in the Description page of Project Settings.

#include "Campus/AI/Services/CanISeeYouService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Campus/AI/AIDrone/CoreDrone/AIAnimDrone.h"
#include "Campus/AI/AIDrone/Components/AIDronePerceptionComponent.h"

UCanISeeYouService::UCanISeeYouService()
{
	NodeName = "Can I See you?";
}

void UCanISeeYouService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	const AAIController* Controller = OwnerComp.GetAIOwner();
	
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Blackboard) return;
	
	UActorComponent* const Component = Controller->GetComponentByClass(UAIDronePerceptionComponent::StaticClass());
	
	UAIDronePerceptionComponent* const PerceptionComponent = Cast<UAIDronePerceptionComponent>(Component);
	if (!PerceptionComponent) return;

	AActor* const Character = Cast<AActor>(Blackboard->GetValueAsObject(CharacterActorKey.SelectedKeyName));
	if (!Character) return;

	if (PerceptionComponent->CanISee(Character))
	{
		Blackboard->SetValueAsBool(ISeeYouKey.SelectedKeyName, true);
		Blackboard->SetValueAsVector(LastLocationKey.SelectedKeyName, PerceptionComponent->GetLastLocationOfInteractionCharacter());
	}
	else
	{
		Blackboard->SetValueAsBool(ISeeYouKey.SelectedKeyName, false);
	}
}
