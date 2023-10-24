// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HTTPGameAPIStructures.generated.h"


//////////LOGIN_STRUCTURES 
USTRUCT(BlueprintType)
struct FLoginRequest
{
	GENERATED_BODY()
	
	UPROPERTY()
	FString Login;
	
	UPROPERTY()
	FString Password;
};

USTRUCT(BlueprintType)
struct FLoginResponse
{
	GENERATED_BODY()
	
	UPROPERTY()
	FString Token;
};
//////////REGISTER_STRUCTURES
USTRUCT(BlueprintType)
struct FRegisterRequest
{
	GENERATED_BODY()
	
	UPROPERTY()
	FString Nickname;
	
	UPROPERTY()
	FString Email;
	
	UPROPERTY()
	FString Login;
	
	UPROPERTY()
	FString Password;
};

USTRUCT(BlueprintType)
struct FRegisterResponse
{
	GENERATED_BODY()
	
	UPROPERTY()
	FString Token;
};
//////////USER_INFO_STRUCTURES
USTRUCT(BlueprintType)
struct FUserInfoRequest
{
	GENERATED_BODY()
	
	UPROPERTY()
	FString Token;
};

USTRUCT(BlueprintType)
struct FUserInfoResponse
{
	GENERATED_BODY()

	UPROPERTY()
	FString UserID;
	
	UPROPERTY()
	FString Nickname;
	
	UPROPERTY()
	FString Email;
};

///SERVERS_INFO_STRUCTURES

USTRUCT(BlueprintTYpe)
struct FServerInfo
{
	GENERATED_BODY()
	UPROPERTY()
	FString Port;
	UPROPERTY()
	int32 ConnectedClients;
};


/////////////ERROR_STRUCT 
USTRUCT(BlueprintType)
struct FErrorResponse
{
	GENERATED_BODY()
	
	UPROPERTY()
	FString Error;
};

