// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CreateSessionWidget.generated.h"

class UCheckBox;
class UEditableText;
class UButton;

/**
 * 
 */
UCLASS()
class CAMPUS_API UCreateSessionWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	UEditableText* SessionNameField;

	UPROPERTY(meta = (BindWidget))
	UEditableText* MaxPlayersCountField;

	UPROPERTY(meta = (BindWidget))
	UCheckBox* LanSessionCheckBox;

	UPROPERTY(meta = (BindWidget))
	UButton* CreateSessionButton;

protected:
	UFUNCTION()
	void OnCreateSessionButtonClicked();
	virtual void NativeOnInitialized() override;
};
