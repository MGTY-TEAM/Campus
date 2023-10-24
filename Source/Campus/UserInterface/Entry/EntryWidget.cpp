// Fill out your copyright notice in the Description page of Project Settings.


#include "EntryWidget.h"

#include "LoginWidget.h"
#include "RegisterWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "Engine/Engine.h"

void UEntryWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (IsValid(LoginWidgetClass) && IsValid(RegisterWidgetClass))
	{
		M_LoginWidget = CreateWidget<ULoginWidget>(this, LoginWidgetClass);
        M_RegisterWidget = CreateWidget<URegisterWidget>(this, RegisterWidgetClass);

		if (IsValid(M_LoginWidget) && IsValid(M_RegisterWidget))
		{
			WidgetSwitcher->AddChild(M_LoginWidget);
			WidgetSwitcher->AddChild(M_RegisterWidget);
			WidgetSwitcher->SetActiveWidget(M_LoginWidget);
			SwitchEntryTypeButtonText->SetText(FText::FromString("Register"));
			
			SwitchEntryTypeButton->OnClicked.AddDynamic(this, &UEntryWidget::OnSwitchEntryTypeButtonClicked);
			
			M_LoginWidget->OnFormExecute.AddDynamic(this, &UEntryWidget::OnLoginExecute);
			M_RegisterWidget->OnFormExecute.AddDynamic(this, &UEntryWidget::OnRegisterExecute);
		}
	}
}

void UEntryWidget::OnSwitchEntryTypeButtonClicked()
{
	if (WidgetSwitcher->GetActiveWidget() == M_LoginWidget)
	{
		WidgetSwitcher->SetActiveWidget(M_RegisterWidget);
		SwitchEntryTypeButtonText->SetText(FText::FromString("Login"));
	}
	else
	{
		WidgetSwitcher->SetActiveWidget(M_LoginWidget);
		SwitchEntryTypeButtonText->SetText(FText::FromString("Register"));
	}
}
//TO DO:
void UEntryWidget::OnLoginExecute(const FString& Token)
{
	OnEntryExecute.Broadcast(Token);
}

void UEntryWidget::OnRegisterExecute(const FString& Token)
{
	OnEntryExecute.Broadcast(Token);
}
