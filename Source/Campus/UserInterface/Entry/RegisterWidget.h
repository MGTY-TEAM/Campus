// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "..\..\Interfaces\Form\FormExecutable.h"
#include "Blueprint/UserWidget.h"
#include "RegisterWidget.generated.h"

class UEditableTextBox;
class UTextBlock;
class UButton;

/**
 * Widget for user registration.
 */
UCLASS()
class CAMPUS_API URegisterWidget : public UUserWidget, public IFormExecutable
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

private:
	/** Text box for login input. */
	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* LoginText;

	/** Text box for password input. */
	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* PasswordText;

	/** Text box for confirming password input. */
	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* ConfirmPasswordText;

	/** Text box for email input. */
	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* EmailText;

	/** Text box for nickname input. */
	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* NicknameText;

	/** Text block for displaying errors. */
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ErrorText;

	/** Button for registering. */
	UPROPERTY(meta = (BindWidget))
	UButton* RegisterButton;

	/** Callback function for register button click event. */
	UFUNCTION()
	void OnRegisterButtonClicked();

	/** Get string value from editable text box. */
	FString GetStringValueFromEditableTextBox(UEditableTextBox* EditableTextBox) const;
};

