// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MultiplayerController.generated.h"

/**
 * 
 */
UCLASS()
class CAMPUS_API AMultiplayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UFUNCTION()
	void SetupPlayerName();
	virtual void BeginPlay() override;
};
