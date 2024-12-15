// Fill out your copyright notice in the Description page of Project Settings.


#include "Campus/AI/Services/CheckObstacleService.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Campus/AI/AIDrone/Components/AIDronePerceptionComponent.h"

UCheckObstacleService::UCheckObstacleService()
{
	NodeName = "Check Obstacle";
}

void UCheckObstacleService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	const AAIController* Controller = OwnerComp.GetAIOwner();
	UAIDronePerceptionComponent* PerceptionComponent = Cast<UAIDronePerceptionComponent>(Controller->GetComponentByClass(UAIDronePerceptionComponent::StaticClass()));
	if (!PerceptionComponent) return;

	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Blackboard) return;

	AActor* Character = Cast<AActor>(Blackboard->GetValueAsObject(CharacterActorKey.SelectedKeyName));
	Blackboard->SetValueAsBool(IsThereObstacleKey.SelectedKeyName, PerceptionComponent->CheckObstacleInFrontOfTarget(Character));
}
