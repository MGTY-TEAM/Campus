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
	UWorld * World = GetWorld();
	
	World->GetFirstPlayerController()->bShowMouseCursor = true;
	World->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly());

	M_EntryWidget = CreateWidget<UEntryWidget>(World, EntryWidgetClass);
	M_EntryWidget->AddToViewport();

	M_EntryWidget->OnEntryExecute.AddDynamic(this, &AEntryGameMode::OnEntryWidgetExecute);

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
			UserGameInstance->TryToGetAndFillUserInfoAndOpenMainMenu();
			
			UE_LOG(LogTemp, Warning, TEXT("Entry is finished!"));
		}
		M_EntryWidget->RemoveFromParent();
	}
}
