// Fill out your copyright notice in the Description page of Project Settings.


#include "DroneGuide.h"

#include "TimerManager.h"
#include "../../UserInterface/ChatBox.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "Campus/Core/BaseCharacter/BaseFirstPersonCharacter.h"
#include "Components/StaticMeshComponent.h"


void ADroneGuide::TeleportToLocation(int index)
{
	TeleportationPlace = Cast<ATeleportationPlane>(TeleportationPlaces[index]);
	UE_LOG(LogTemp, Warning, TEXT("DroneTeleport"));
	if (TeleportationPlace)
	{
		if (InteractCharacter)
		{
			InteractCharacter->SetActorLocation(TeleportationPlace->PlayerPlane->GetComponentLocation());
			SetActorLocation(TeleportationPlace->RobotPlane->GetComponentLocation());
		}
	}
}

void ADroneGuide::DarkeningScreen()
{
	DarkWidget = CreateWidget<UDarkeningScreen>(GetWorld()->GetFirstPlayerController(), BlueprintDarkeningClass);
	DarkWidget->AddToPlayerScreen();
	GetWorld()->GetTimerManager().SetTimer(EndDarkeningTimer, this, &ADroneGuide::EndDarkeningScreen, 1.5f, false);
	UE_LOG(LogTemp, Warning, TEXT("Daaark"));
}

void ADroneGuide::EndDarkeningScreen()
{
	DarkWidget->RemoveFromParent();
}

void ADroneGuide::BeginPlay()
{
	Super::BeginPlay();
	ChangeState(EDroneGuide::Drone_Idle);
	
	ChatWidget = CreateWidget<UChatBox>(GetWorld()->GetFirstPlayerController(), BlueprintChatClass);
	
	if (ChatWidget)
	{
		ChatWidget->TeleportationEvent.AddDynamic(this, &ADroneGuide::TeleportToLocation);
		ChatWidget->DarkeningEvent.AddDynamic(this, &ADroneGuide::DarkeningScreen);
	}
	
}

void ADroneGuide::UnPickupOn(AActor* Character)
{
	Super::UnPickupOn(Character);
	InteractCharacter = Cast<ABaseFirstPersonCharacter>(Character);
	ChangeState(EDroneGuide::Drone_PlayerInteract);
	OpenChat();
}

void ADroneGuide::UnPickupOff()
{
	Super::UnPickupOff();
	ChangeState(EDroneGuide::Drone_Idle);
	CloseChat();
}

void ADroneGuide::ChangeState(EDroneGuide State, float Duration)
{
	switch (State)
	{
	case EDroneGuide::Drone_Idle:
		StartIdleAnim();
		StopRotateToPlayerAnim();
		break;
	case EDroneGuide::Drone_PlayerInteract:
		StartRotateToPlayerAnim();
		break;
	}
}

void ADroneGuide::StartIdleAnim()
{
	Super::StartIdleAnim();
}

void ADroneGuide::StopIdleAnim()
{
	Super::StopIdleAnim();
}

void ADroneGuide::StartRotateToPlayerAnim()
{
	Super::StartRotateToPlayerAnim();
}

void ADroneGuide::StopRotateToPlayerAnim()
{
	Super::StopRotateToPlayerAnim();
}

void ADroneGuide::OpenChat()
{
	if (!ChatWidget->IsInViewport())
	{
		ChatWidget->AddToPlayerScreen();
		UE_LOG(LogTemp, Warning, TEXT("AddToScreen"));
	}
	ChatWidget->SetVisibility(ESlateVisibility::Visible);
}

void ADroneGuide::CloseChat()
{
	ChatWidget->SetVisibility(ESlateVisibility::Hidden);
}


