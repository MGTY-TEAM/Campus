// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultAnimDrone.h"

#include "TimerManager.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/KismetMathLibrary.h"


void ADefaultAnimDrone::BeginPlay()
{
	Super::BeginPlay();
}

void ADefaultAnimDrone::StartIdleAnim()
{
	GetWorld()->GetTimerManager().SetTimer(IdleAnimTimer, this, &ADefaultAnimDrone::StartIdleAnim, 0.01f, true);
	float TimeSeconds = GetWorld()->GetTimeSeconds();
	float Movement = (sin(TimeSeconds * Frequency) * Amplitude) + Body->GetComponentLocation().Z;
	Body->SetWorldLocation(FVector(Body->GetComponentLocation().X, Body->GetComponentLocation().Y, Movement));
}

void ADefaultAnimDrone::StopIdleAnim()
{
	GetWorldTimerManager().ClearTimer(IdleAnimTimer);
}

void ADefaultAnimDrone::StartRotateToPlayerAnim()
{
	GetWorld()->GetTimerManager().SetTimer(RotateToPlayerTimer, this, &ADefaultAnimDrone::StartRotateToPlayerAnim, 0.01f, true);
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

void ADefaultAnimDrone::StopRotateToPlayerAnim()
{
	GetWorldTimerManager().ClearTimer(RotateToPlayerTimer);
}
