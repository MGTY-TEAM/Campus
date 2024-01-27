// Fill out your copyright notice in the Description page of Project Settings.
// https://github.com/MEgorov4/Kampus/wiki/HTTP-Requests-System
#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IHttpRequest.h"
#include "HTTPAiMyLogicRequestsLib.generated.h"
DECLARE_LOG_CATEGORY_EXTERN(LogRequests, Log, All);
 
/**
 * 
 */
UCLASS()
class CAMPUS_API UHTTPAiMyLogicRequestsLib : public UObject
{
	GENERATED_BODY()

public:
	
	static FString& CURRENT_GAME_ID;
	static void AIMyLogicGetRequest(TFunction<void(const FString&, const FString&, const int&)> CallBack, const FString& StringRequest, const FString& URL);
	
	static void MakeMove(const FString& GameId, const FString& Move, bool OfferingDraw);

	static void CreateGameWithAI(TFunction<void(const FString&)> CallBack, const FString& Level, bool Clock, const FString& Time, const FString& Increment);
	static void StreamGameMoves(TFunction<void(const FString&)> CallBack, const FString& GameId);
};
