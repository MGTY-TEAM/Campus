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
 * 
 */
UCLASS()
class CAMPUS_API URegisterWidget : public UUserWidget, public IFormExecutable
{
	GENERATED_BODY()
protected:
	virtual void NativeOnInitialized() override;

private:
	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* LoginText;

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* PasswordText;

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* ConfirmPasswordText;

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* EmailText;

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* NicknameText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ErrorText;

	UPROPERTY(meta = (BindWidget))
	UButton* RegisterButton;

	UFUNCTION()
	void OnRegisterButtonClicked();

	FString GetStringValueFromEditableTextBox(UEditableTextBox* EditableTextBox) const;
};
