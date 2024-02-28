// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/EditableTextBox.h"
#include "AuthorizationWidget.generated.h"

/**
 * 
 */

UCLASS()
class CAMPUS_API UAuthorizationWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UTextBlock* TextIncorrect;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextRegistration;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextForgotPassword;
	
	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* TextBoxLogin;
	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* TextBoxPassword;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* ButtonAuthorization;
	
};
