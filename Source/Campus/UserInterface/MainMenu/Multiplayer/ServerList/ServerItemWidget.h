// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSessionSettings.h"
#include "Blueprint/UserWidget.h"
#include "ServerItemWidget.generated.h"

/**
 * 
 */
DECLARE_DELEGATE_OneParam(FOnConnectButtonClicked, FOnlineSessionSearchResult SessionSearchResult);

class UTextBlock;
class UButton;

UCLASS()
class CAMPUS_API UServerItemWidget : public UUserWidget
{
	GENERATED_BODY()
	UPROPERTY(meta = (BindWidget))
	UButton* ConnectButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayersCountText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MaxPlayersCountText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SessionIDText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PingText;

public:
	UFUNCTION()
	void OnButtonClicked();

	UFUNCTION()
	void SetServerItemInfo(const FString& MaxPlayersCount, const FString& PlayersCount, const FString& SessionID,
	                       const FString& SessionPing, FOnlineSessionSearchResult SessionSearchResult);
	FOnConnectButtonClicked OnConnectButtonClicked;
	
	virtual void NativeOnInitialized() override;
	
	FOnlineSessionSearchResult SessionSearchResult;
};
