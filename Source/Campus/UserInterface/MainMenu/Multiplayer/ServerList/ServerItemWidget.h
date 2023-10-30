// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ServerItemWidget.generated.h"

/**
 * 
 */

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
	UTextBlock* PlayersMaxCountText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ServerName;

public:
	UFUNCTION()
	void OnConnectButtonClicked();
	virtual void NativeOnInitialized() override;
	
};
