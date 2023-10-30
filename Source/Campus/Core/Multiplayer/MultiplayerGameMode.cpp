// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerGameMode.h"

#include "Campus/Core/UserGameInstance.h"
#include "Campus/Libraries/Requests/GameAPI/HTTPGameAPIRequestsLib.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"

void AMultiplayerGameMode::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		PlayerController->SetInputMode(FInputModeGameOnly());
		PlayerController->bShowMouseCursor = false;
	}
}

void AMultiplayerGameMode::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);
	FString Nickname;
	if (UWorld* World = GetWorld())
	{
		FString URL = World->GetAddressURL();
		FString FinedString = "Nickname";
		UGameplayStatics::GetKeyValue(URL, FinedString, Nickname);
	}

	if (!Nickname.IsEmpty() && NewPlayer->PlayerState)
	{
		NewPlayer->PlayerState->SetPlayerName(Nickname);
	}
}
