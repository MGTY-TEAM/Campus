// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniGameInfo.h"
#include "UObject/Interface.h"

#include "MiniGames.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMiniGameComplited, UMiniGameInfo*, MiniGameInfo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMiniGameError);

UINTERFACE()
class UMiniGames : public UInterface
{
	GENERATED_BODY()
};

class CAMPUS_API IMiniGames
{
	GENERATED_BODY()

public:
	FOnMiniGameComplited ExecuteMiniGameCompleted;
	FOnMiniGameError ExecuteMiniGameError;

	UMiniGameInfo* MiniGameInfo = nullptr;
};
