// Fill out your copyright notice in the Description page of Project Settings.
// https://github.com/MEgorov4/Kampus/wiki/HTTP-Requests-System
#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IHttpRequest.h"
#include "HTTPAiMyLogicRequestsLib.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogRequests, Log, All);

/**
 * Library for handling HTTP requests related to AI logic in the game.
 */
UCLASS()
class CAMPUS_API UHTTPAiMyLogicRequestsLib : public UObject
{
	GENERATED_BODY()

public:
	/** Socket for handling HTTP requests. */
	static FSocket* Socket;

	/** Current game ID. */
	static FString& CURRENT_GAME_ID;

	/**
	 * Perform a GET request to the AI logic server.
	 *
	 * @param CallBack Callback function to execute after the request is complete.
	 * @param StringRequest The request string.
	 * @param URL The URL to send the request to.
	 */
	static void AIMyLogicGetRequest(TFunction<void(const FString&, const FString&, const int&)> CallBack, const FString& StringRequest, const FString& URL);

	/**
	 * Make a move in the game.
	 *
	 * @param CallBack Callback function to execute after the request is complete.
	 * @param GameId The ID of the game.
	 * @param Move The move to make.
	 */
	static void MakeMove(TFunction<void(bool, const FString&, const FString&, const FString&)> CallBack, const FString& GameId, const FString& Move);

	/**
	 * Create a new game with AI opponent.
	 *
	 * @param CallBack Callback function to execute after the request is complete.
	 * @param StartWithWhite Whether to start the game with white pieces.
	 */
	static void CreateGameWithAI(TFunction<void(const FString&)> CallBack, bool StartWithWhite);

	/**
	 * Make a move by AI in the game.
	 *
	 * @param CallBack Callback function to execute after the request is complete.
	 * @param GameId The ID of the game.
	 */
	static void MakeAiMove(TFunction<void(const FString&, const FString&, const FString&, const FString&)> CallBack, const FString& GameId);
};

