// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "BotMessageHandler.generated.h"

/**
 * 
 */
UCLASS()
class CAMPUS_API UBotMessageHandler : public UObject
{
	GENERATED_BODY()

	static TMap<int, FString> LocationIDToLocationInfo;
	
public:
	static TPair<int, FString> HandleMessage(FString Message);
	
};
