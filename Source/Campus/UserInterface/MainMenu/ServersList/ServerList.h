// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ServerList.generated.h"

class UButton;
class UVerticalBox;
class UServerItem;
/**
 * 
 */
UCLASS()
class CAMPUS_API UServerList : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UServerItem> ServerItemClass;
	
	TArray<UServerItem*> ServerItemList;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* ServerListBox;

	UPROPERTY(meta = (BindWidget))
	UButton* UpdateServerListButton;
	
	UFUNCTION()
	void UpdateServerListButtonClicked();

	UFUNCTION()
	void OnConnectButtonClicked(const FString& Port);
protected:
	virtual void NativeOnInitialized() override;
	
};
