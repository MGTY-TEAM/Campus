// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "..\..\..\Interfaces\Form\FormExecutable.h"
#include "Blueprint/UserWidget.h"
#include "ServerItem.generated.h"

class UTextBlock;
class UButton;
/**
 * 
 */
UCLASS()
class CAMPUS_API UServerItem : public UUserWidget, public IFormExecutable
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	UButton* ConnectButton;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* PortText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ClientsCountText;

	
public:

	void SetInfo(FString Port, int32 ClientsCount);

	void UpdateClientsCount(int32 ClientsCount);

	FString GetPort();

protected:
	UFUNCTION()
	void OnConnectionButtonClicked();
	
	virtual void NativeOnInitialized() override;
};
