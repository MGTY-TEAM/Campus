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

AAIAnimDrone::AAIAnimDrone()
{

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AAIDroneController::StaticClass();

	if (!ChatUserComponent)
	{
		ChatUserComponent = CreateDefaultSubobject<UChatUserComponent>("ChatUserComponent");
	}
	
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

	ChatWidget = CreateWidget<UChatBox>(GetWorld()->GetFirstPlayerController(), BlueprintChatClass);

	StartLocationOfDrone = GetActorLocation();
	
	if (UChatManager::RegisterUser("Bot", ChatUserComponent))
	{
		UE_LOG(LogTemp, Warning, TEXT("BotRegistered"));
		ChatUserComponent->OnMessageReceived.BindUObject(this, &AAIAnimDrone::ReceiveMessage);
	}
	
	/*if (ChatWidget)
	{
		ChatWidget->TeleportationEvent.AddDynamic(this, &AAIAnimDrone::TeleportToLocation);
		ChatWidget->DarkeningEvent.AddDynamic(this, &AAIAnimDrone::DarkeningScreen);
	}*/
}


void AAIAnimDrone::ReceiveMessage(UMessageInstance* MessageInstance)
{
	MessageInstance->GetMessageInfo().Get<2>();
}

void AAIAnimDrone::UnPickupOn(AActor* Character)
{
	Super::UnPickupOn(Character);

	InInteraction = true;
	InteractingCharacter = Character;
}

void AAIAnimDrone::UnPickupOff()
{
	Super::UnPickupOff();

	InInteraction = false;
	InteractingCharacter = nullptr;
	StopRotateToPlayerAnim();
	CloseChat();

	// AAIDroneController* AController = Cast<AAIDroneController>(GetController());
	// AController->ClearFocus(EAIFocusPriority::Gameplay);
}


TTuple<FString, FString, int> AAIAnimDrone::GetResponceMessage(UMessageInstance* MessageInstance)
{
	

	return TTuple<FString, FString, int>();
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

UChatBox* AAIAnimDrone::OpenChat()
{
	if (!ChatWidget->IsInViewport())
	{
		ChatWidget->AddToPlayerScreen();
		UE_LOG(LogTemp, Warning, TEXT("AddToScreen"));
	}
	ChatWidget->SetVisibility(ESlateVisibility::Visible);
	return ChatWidget;
}

void AAIAnimDrone::CloseChat()
{
	ChatWidget->SetVisibility(ESlateVisibility::Hidden);
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
