// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerGameState.h"

#include "GameFramework/PlayerState.h"

AMultiplayerGameState::AMultiplayerGameState()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMultiplayerGameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	UE_LOG(LogTemp, Error, TEXT("MultiplayerGameState"));
	
	if (PlayerArray.Num())
	{
		for (APlayerState* PlayerState : PlayerArray)
		{
			if (PlayerState)
			{
				UE_LOG(LogTemp, Error, TEXT("User: %s"), *PlayerState->GetPlayerName());
			}
		}
	}
}
