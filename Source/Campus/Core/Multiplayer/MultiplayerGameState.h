// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "MultiplayerGameState.generated.h"

/**
 * 
 */
UCLASS()
class CAMPUS_API AMultiplayerGameState : public AGameState
{
	GENERATED_BODY()
	
public:
	AMultiplayerGameState();
	
	virtual void Tick(float DeltaSeconds) override;
};