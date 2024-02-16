// Fill out your copyright notice in the Description page of Project Settings.


#include "Campus/AI/AIDrone/CoreDrone/AIAnimDrone.h"
#include "Campus/AI/AIDroneController.h"
#include "Campus/Drone/TeleportationPlane.h"
#include "Campus/UserInterface/ChatBox.h"
#include "Campus/UserInterface/DarkeningScreen.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/Engine.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"
#include "Campus/Chat/ChatManager.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/SplineComponent.h"
#include "Campus/Chat/ChatUserComponent.h"
#include "Campus/Libraries/Requests/Services/HTTPAiMyLogicRequestsLib.h"
#include "Kismet/GameplayStatics.h"

AAIAnimDrone::AAIAnimDrone()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AAIDroneController::StaticClass();
	
	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SceneComponent->SetupAttachment(GetRootComponent());

	SplineComponent = CreateDefaultSubobject<USplineComponent>("SplineComponent");
	SplineComponent->SetupAttachment(GetRootComponent());

	
	bUseControllerRotationYaw = false;
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, DroneRotationSpeed, 0.0f);
	}
	
}


void AAIAnimDrone::BeginPlay()
{
	Super::BeginPlay();


	StartLocationOfDrone = GetActorLocation();
	



}

void AAIAnimDrone::StartRotateToPlayerAnim()
{
	GetWorld()->GetTimerManager().SetTimer(RotateToPlayerTimer, this, &AAIAnimDrone::StartRotateToPlayerAnim, 0.01f,
	                                       true);
	FVector StartLocation = GetCapsuleComponent()->GetComponentLocation(); // Starting position of the drone
	FVector TargetLocation = GetWorld()->GetFirstPlayerController()->GetCharacter()->GetActorLocation();
	// Player's position

	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(StartLocation, TargetLocation);
	// Calculates the look-at vector from the drone to the player
	FRotator StartRotation = GetCapsuleComponent()->GetComponentRotation(); // Starting rotation of the drone
	FRotator EndRotation = LookAtRotation; // Final rotation - look at the player

	// Calculates the interpolated rotation
	FRotator InterpolatedRotation = FMath::RInterpTo(StartRotation, EndRotation, GetWorld()->GetDeltaSeconds(),
	                                                 RotationSpeed);
	// Applies the interpolated rotation to the capsule component
	GetCapsuleComponent()->SetWorldRotation(InterpolatedRotation);
}

void AAIAnimDrone::StopRotateToPlayerAnim()
{
	GetWorldTimerManager().ClearTimer(RotateToPlayerTimer);
}

UChatBox* AAIAnimDrone::OpenChat()
{
	return ChatWidget;
}

void AAIAnimDrone::CloseChat()
{
}

void AAIAnimDrone::TeleportToLocation(int index)
{
	TeleportationPlace = Cast<ATeleportationPlane>(TeleportationPlaces[index]);
	UE_LOG(LogTemp, Warning, TEXT("DroneTeleport"));
	if (TeleportationPlace)
	{
		if (InteractingCharacter)
		{
			InteractingCharacter->SetActorLocation(TeleportationPlace->PlayerPlane->GetComponentLocation());
			SetActorLocation(TeleportationPlace->RobotPlane->GetComponentLocation());
		}
	}
}

void AAIAnimDrone::DarkeningScreen()
{
	DarkWidget = CreateWidget<UDarkeningScreen>(GetWorld()->GetFirstPlayerController(), BlueprintDarkeningClass);
	DarkWidget->AddToPlayerScreen();
	GetWorld()->GetTimerManager().SetTimer(EndDarkeningTimer, this, &AAIAnimDrone::EndDarkeningScreen, 1.5f, false);
	UE_LOG(LogTemp, Warning, TEXT("Daaark"));
}

void AAIAnimDrone::EndDarkeningScreen()
{
	DarkWidget->RemoveFromParent();
}
