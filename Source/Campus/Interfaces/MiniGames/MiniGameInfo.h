// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MiniGameInfo.generated.h"

/**
 *
 */
UCLASS()
class CAMPUS_API UMiniGameInfo : public UObject
{
	GENERATED_BODY()

public:
	FString Title;
	FString Description;

	void SetupInfo(const FString& NewTitle, const FString& NewDescription);
};
