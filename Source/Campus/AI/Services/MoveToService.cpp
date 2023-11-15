// Fill out your copyright notice in the Description page of Project Settings.


#include "Campus/AI/Services/MoveToService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Campus/AI/AIDrone/CoreDrone/AIAnimDrone.h"
#include "Components/CapsuleComponent.h"

UMoveToService::UMoveToService()
{
	NodeName = "Move To";
}

void UMoveToService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAIController* const Controller = OwnerComp.GetAIOwner();
	AAIAnimDrone* const Drone = Cast<AAIAnimDrone>(Controller->GetPawn());
	if (!Drone) return;

	UBlackboardComponent* const Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Blackboard) return;

	FVector CurrentLocation = Drone->GetActorLocation();
	FVector TargetLocation = Blackboard->GetValueAsVector(NewLocationKey.SelectedKeyName);

	//if (CurrentLocation.Equals(TargetLocation, 100)) return;

	FVector InterpolatedLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaSeconds, InterpSpeed);

	Drone->GetCapsuleComponent()->SetWorldLocation(InterpolatedLocation);
}
