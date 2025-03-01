// Fill out your copyright notice in the Description page of Project Settings.


#include "Campus/AI/Services/WhatCharacterDoService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Campus/Core/CharacterSystem/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

UWhatCharacterDoService::UWhatCharacterDoService()
{
	NodeName = "What Does Character Do?";
}

void UWhatCharacterDoService::OnSearchStart(FBehaviorTreeSearchData& SearchData)
{
	Super::OnSearchStart(SearchData);

	Blackboard = SearchData.OwnerComp.GetBlackboardComponent();
	if (!Blackboard) return;

	Character = Cast<AActor>(Blackboard->GetValueAsObject(CharacterActorKey.SelectedKeyName));
	if (!Character) return;

	Drone = Cast<AActor>(Blackboard->GetValueAsObject(SelfActorKey.SelectedKeyName));
	if (!Drone) return;
	
	DistanceLastTick = (Character->GetActorLocation() - Drone->GetActorLocation()).Size();
}

void UWhatCharacterDoService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (Blackboard)
	{
		Blackboard->SetValueAsBool(IsHeStandingKey.SelectedKeyName,IsHeStanding());
		Blackboard->SetValueAsBool(IsHeGettingCloserKey.SelectedKeyName,IsHeGettingCloser());
	}
}

bool UWhatCharacterDoService::IsHeStanding() const
{
	if (!Character) return false;
	
	const ABaseCharacter* Player = Cast<ABaseCharacter>(Character);
	if (!Player) return false;

	if (Player->GetCharacterMovement()->Velocity.IsZero())
	{
		return true;
	}

	return false;
}

bool UWhatCharacterDoService::IsHeGettingCloser()
{
	if (!Character || !Drone) return false;

	const double DistanceOnThisTick = (Character->GetActorLocation() - Drone->GetActorLocation()).Size();

	if (DistanceLastTick > DistanceOnThisTick)
	{
		DistanceLastTick = (Character->GetActorLocation() - Drone->GetActorLocation()).Size();
		return true;
	}
	DistanceLastTick = (Character->GetActorLocation() - Drone->GetActorLocation()).Size();
	return false;
}
