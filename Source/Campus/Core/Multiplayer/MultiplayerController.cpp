// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerController.h"

#include "Campus/Core/UserGameInstance.h"
#include "GameFramework/PlayerState.h"


void AMultiplayerController::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle TimerHandle;

}

void AMultiplayerController::SetupPlayerName()
{
	/*UUserGameInstance* UserGameInstance = Cast<UUserGameInstance>(GetGameInstance());
	if (UserGameInstance)
	{
		if (PlayerState)
		{
			PlayerState->SetPlayerName(UserGameInstance->GetNickname());
			if (PlayerState->GetIsReplicated())
			{
				UE_LOG(LogTemp, Error, TEXT("PlayerState IS Replicable"));
				PlayerState->BeginReplication();
			}
		}
	}*/
}
