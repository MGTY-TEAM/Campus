// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuGameMode.h"

#include "Blueprint/UserWidget.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"


AMainMenuGameMode::AMainMenuGameMode()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AMainMenuGameMode::BeginPlay()
{
	Super::BeginPlay();

	UWorld * World = GetWorld();
	World->GetFirstPlayerController()->bShowMouseCursor = true;
	World->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly());

	UGameplayStatics::GetGameInstance(World);

	MainMenuWidget = CreateWidget<UUserWidget>(World, MainMenuWidgetClass);

	if (MainMenuWidget)
	{
		MainMenuWidget->AddToViewport();
	}
}



