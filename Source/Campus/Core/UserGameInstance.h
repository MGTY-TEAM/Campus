// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "UserGameInstance.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FUserInfo
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadOnly, Category = "User") FString Nickname;
	UPROPERTY(BlueprintReadOnly, Category = "User") FString Email;
	UPROPERTY(BlueprintReadOnly, Category = "User") FString ID;
	
};

UCLASS()
class CAMPUS_API UUserGameInstance : public UGameInstance
{
	GENERATED_BODY()


public:
	
	const FString& GetUserID() const;
	const FString& GetUserToken() const;
	const FString& GetNickname() const;
	const FString& GetEmail() const;
	const FString& GetGameServerPort() const;

	void SetUserToken(const FString& Token);
	
	bool TryToGetAndFillUserInfoAndOpenMainMenu();
	bool TryConnectToGameServerAndOpenMultiplayerMap(const FString& Port);

private:

	FUserInfo M_UserInfo;
	
	FString M_UserToken;
	FString M_GameServerPort;
};
