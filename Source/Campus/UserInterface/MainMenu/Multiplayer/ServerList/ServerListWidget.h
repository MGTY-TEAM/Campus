// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ServerListWidget.generated.h"

class UButton;
class UServerItemWidget;
class UVerticalBox;
class UUserGameInstance;
/**
 * 
 */
UCLASS()
class CAMPUS_API UServerListWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UServerItemWidget> M_ServerItemWidgetClass;
	
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* M_ServersVerticalBox;

	UPROPERTY(meta = (BindWidget))
	UButton* M_UpdateServerListButton;

	UFUNCTION()
	void OnUpdateServerListButtonClicked();

	UUserGameInstance* M_UserGameInstance;
protected:
	void OnSearchComplete(TArray<FOnlineSessionSearchResult> OnlineSessionSearchResults);
	virtual void NativeOnInitialized() override;
};
