// Fill out your copyright notice in the Description page of Project Settings.


#include "Campus/AI/AIDrone/CoreDrone/AIAnimDrone.h"
#include "Campus/AI/AIDroneController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/Engine.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"

AAIAnimDrone::AAIAnimDrone()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AAIDroneController::StaticClass();

	/*bUseControllerRotationYaw = false;
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
	}*/
}

void AAIAnimDrone::UnPickupOn(AActor* Character)
{
	Super::UnPickupOn(Character);

	InInteraction = true;
	InteractingCharacter = Character;
	StopRotateToPlayerAnim();

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, "Interaction");
}

void AAIAnimDrone::UnPickupOff()
{
	Super::UnPickupOff();

	InInteraction = false;
	InteractingCharacter = nullptr;
	StopRotateToPlayerAnim();

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, "Not Interaction");
}

void AAIAnimDrone::StartRotateToPlayerAnim()
{
	GetWorld()->GetTimerManager().SetTimer(RotateToPlayerTimer, this, &AAIAnimDrone::StartRotateToPlayerAnim, 0.01f, true);
	FVector StartLocation = GetCapsuleComponent()->GetComponentLocation(); // Starting position of the drone
	FVector TargetLocation = GetWorld()->GetFirstPlayerController()->GetCharacter()->GetActorLocation(); // Player's position

	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(StartLocation, TargetLocation); // Calculates the look-at vector from the drone to the player
	FRotator StartRotation = GetCapsuleComponent()->GetComponentRotation(); // Starting rotation of the drone
	FRotator EndRotation = LookAtRotation; // Final rotation - look at the player

	// Calculates the interpolated rotation
	FRotator InterpolatedRotation = FMath::RInterpTo(StartRotation, EndRotation, GetWorld()->GetDeltaSeconds(), RotationSpeed);
	// Applies the interpolated rotation to the capsule component
	GetCapsuleComponent()->SetWorldRotation(InterpolatedRotation);
}

void AAIAnimDrone::StopRotateToPlayerAnim()
{
	GetWorldTimerManager().ClearTimer(RotateToPlayerTimer);
}
