// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HTTPGameAPIStructures.h"
#include "HTTPGameAPIRequestsLib.generated.h"


/**
 * This file defines structures and functions for making HTTP requests to the GameAPI server.
 */

DEFINE_LOG_CATEGORY_STATIC(HTTPGameApiLog, Log, All);

UCLASS()
class CAMPUS_API UHTTPGameAPIRequestsLib : public UObject
{
	GENERATED_BODY()

public:
	/**
	* @brief Create an HTTP request to log in on the GameAPI server.
	* @param CallBack Delegate to call when the request is complete.
	* @param LoginRequest Structure containing the login request.
	*/
	static void GameAPILoginRequest(
		TFunction<void(const bool&, const FLoginResponse&, const FErrorResponse&)> CallBack,
		const FLoginRequest& LoginRequest);

	/**
	* @brief Create an HTTP request to register on the GameAPI server.
	* @param CallBack Delegate to call when the request is complete.
	* @param RegisterRequest Structure containing the register request.
	*/
	static void GameAPIRegisterRequest(
	TFunction<void(const bool&, const FRegisterResponse& , const  FErrorResponse&)> CallBack,
								   const FRegisterRequest& RegisterRequest);

	static void GameAPIUserInfoRequest(
		TFunction<void(const bool&, const FUserInfoResponse&, const FErrorResponse&)> CallBack,
		const FUserInfoRequest& UserInfoRequest);

	static void GameApiServerInfoRequest(TFunction<void(const bool&, const TArray<FServerInfo>&, const FErrorResponse&)> CallBack);
	
private:
	/**
	 * @brief Get a JSON-formatted FString from a Struct.
	 * @tparam TStruct Struct type
	 * @param FilledStruct Struct to extract fields from
	 * @param StringOutput String output
	 * @return Completion status
	 */
	template <typename TStruct>
	static bool GetJsonStringFromStruct(TStruct FilledStruct, FString& StringOutput);

	/**
	 * @brief Get a Struct from a JSON-formatted FString.
	 * @tparam TStruct Struct type 
	 * @param OutputStruct Output struct to be filled from the JSON string
	 * @return Completion status
	 */
	template <typename TStruct>
	static bool GetStructFromJsonString(const FString&, TStruct& OutputStruct);
};
