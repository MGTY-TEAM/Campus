// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SinglePlayerGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CAMPUS_API ASinglePlayerGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;;
};
