// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ServerItemWidget.generated.h"

/**
 * 
 */
DECLARE_DELEGATE_OneParam(FOnConnectButtonClicked, UServerItemWidget*);

class UTextBlock;
class UButton;

UCLASS()
class CAMPUS_API UServerItemWidget : public UUserWidget
{
	GENERATED_BODY()


	
public:
	UPROPERTY(meta = (BindWidget))
	UButton* ConnectButton;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayersCountText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayersMaxCountText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ServerName;
	
	UFUNCTION()
	void OnButtonClicked();
	
	FOnConnectButtonClicked OnConnectButtonClicked;
	virtual void NativeOnInitialized() override;
	
};
