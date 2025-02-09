// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/EditableTextBox.h"
#include "RegistrationWidget.generated.h"

/**
 * 
 */
UCLASS()
class CAMPUS_API URegistrationWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeOnInitialized() override;

	UFUNCTION()
	void OnButtonAuthorizationFormClick();

protected:

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* TextBoxLogin;
	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* TextBoxPassword;
	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* TextBoxRetryPassword;
	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* TextBoxNickName;

	UPROPERTY(meta = (BindWidget))
	class UButton* ButtonRegistration;
	UPROPERTY(Meta = (BindWidget), BlueprintReadWrite)
	UButton* ButtonAuthorizationForm;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextIncorrect;
};
