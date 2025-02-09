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
	
	if (UWorld * World = GetWorld())
	{
		World->GetFirstPlayerController()->bShowMouseCursor = true;
		World->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly());

		UGameplayStatics::GetGameInstance(World);
#ifdef MAIN_MENU_GAME_MODE_DEBUG
		UE_LOG(LogMainMenuGameMode, Log, TEXT("Create main menu widget"));
#endif
		
		M_MainMenuWidget = CreateWidget<UUserWidget>(World, M_MainMenuWidgetClass);

		if (M_MainMenuWidget)
		{
			M_MainMenuWidget->AddToViewport();
		}
	}
}



