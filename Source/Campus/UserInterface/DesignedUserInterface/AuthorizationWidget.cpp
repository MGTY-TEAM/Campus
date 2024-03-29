// Fill out your copyright notice in the Description page of Project Settings.


#include "AuthorizationWidget.h"

#include "Components/Button.h"


void UAuthorizationWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ButtonRegistrationForm->OnClicked.AddDynamic(this, &UAuthorizationWidget::OnRegistrationFormButtonCLick);
}

void UAuthorizationWidget::OnRegistrationFormButtonCLick()
{

	TextBoxLogin->SetText(FText::FromString(""));
	TextBoxPassword->SetText(FText::FromString(""));
}
