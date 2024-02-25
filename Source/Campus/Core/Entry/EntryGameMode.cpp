// Fill out your copyright notice in the Description page of Project Settings.


#include "EntryGameMode.h"


#include "../../Core/UserGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
#include "../../UserInterface/Entry/EntryWidget.h"


AEntryGameMode::AEntryGameMode()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AEntryGameMode::BeginPlay()
{
	if (UWorld* World = GetWorld())
	{
		World->GetFirstPlayerController()->bShowMouseCursor = true;
		World->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly());
#ifdef ENTRY_GAME_MODE_DEBUG
		UE_LOG(LogEntryGameMode, Log, TEXT("Create entry widget"));
#endif
		M_EntryWidget = CreateWidget<UEntryWidget>(World, M_EntryWidgetClass);
		M_EntryWidget->AddToViewport();

		M_EntryWidget->OnEntryExecute.AddDynamic(this, &AEntryGameMode::OnEntryWidgetExecute);
	}
	Super::BeginPlay();
}

void AEntryGameMode::OnEntryWidgetExecute(const FString& Token)
{
	if (!Token.IsEmpty())
	{
		UUserGameInstance* UserGameInstance = Cast<UUserGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		if (UserGameInstance)
		{
			UserGameInstance->SetUserToken(Token);
			UserGameInstance->TryToGetAndFillUserInfoAndTransitToMainMenu();
#ifdef ENTRY_GAME_MODE_DEBUG
			UE_LOG(LogEntryGameMode, Log, TEXT("Entry behavior completed"));
#endif
		}
		M_EntryWidget->RemoveFromParent();
	}
}
