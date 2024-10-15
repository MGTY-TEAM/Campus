// Fill out your copyright notice in the Description page of Project Settings.


#include "RegistrationWidget.h"

#include "Components/Button.h"
#include "Components/EditableText.h"

void URegistrationWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ButtonAuthorizationForm->OnClicked.AddDynamic(this, &URegistrationWidget::OnButtonAuthorizationFormClick);
}

void URegistrationWidget::OnButtonAuthorizationFormClick()
{
	TextBoxLogin->SetText(FText::FromString(""));
	TextBoxPassword->SetText(FText::FromString(""));

	TextBoxRetryPassword->SetText(FText::FromString(""));
	TextBoxNickName->SetText(FText::FromString(""));
}
