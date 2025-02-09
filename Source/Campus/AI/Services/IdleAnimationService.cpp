// Fill out your copyright notice in the Description page of Project Settings.


#include "Campus/AI/Services/IdleAnimationService.h"
#include "Campus/AI/AIDroneController.h"
#include "Campus/AI/AIDrone/CoreDrone/AIAnimDrone.h"

void UIdleAnimationService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const AAIController* Controller = OwnerComp.GetAIOwner();
	const AAIAnimDrone* Drone = Cast<AAIAnimDrone>(Controller->GetPawn());

	if (Drone)
	{
		float TimeSeconds = GetWorld()->GetTimeSeconds();
		float Movement = (sin(TimeSeconds * Frequency) * Amplitude) + Drone->Body->GetComponentLocation().Z;
		Drone->Body->SetWorldLocation(FVector(Drone->Body->GetComponentLocation().X, Drone->Body->GetComponentLocation().Y, Movement));
	}
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
