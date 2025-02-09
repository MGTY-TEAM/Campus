// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "..\..\Interfaces\Form\FormExecutable.h"
#include "Blueprint/UserWidget.h"
#include "LoginWidget.generated.h"

class UEditableTextBox;
class UTextBlock;
class UButton;

/**
 * Widget for user login.
 */
UCLASS()
class CAMPUS_API ULoginWidget : public UUserWidget, public IFormExecutable
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

	/** Text block for displaying errors. */
	UPROPERTY(meta =(BindWidget))
	UTextBlock* ErrorText;

	/** Button for login. */
	UPROPERTY(meta =(BindWidget))
	UButton* LoginButton;

	/** Get string value from editable text box. */
	FString GetStringValueFromEditableTextBox(UEditableTextBox* EditableTextBox) const;

	/** Callback function for login button click event. */
	UFUNCTION()
	void OnLoginButtonClicked();
};

