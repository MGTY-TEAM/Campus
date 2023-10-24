// Fill out your copyright notice in the Description page of Project Settings.


#include "RegisterWidget.h"

#include "Campus/Libraries/Requests/GameAPI/HTTPGameAPIRequestsLib.h"
#include "Campus/Libraries/Requests/GameAPI/HTTPGameAPIStructures.h"
#include "Campus/Libraries/Validation/FormFieldsValidatorLib.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"


void URegisterWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	RegisterButton->OnClicked.AddDynamic(this, &URegisterWidget::OnRegisterButtonClicked);
}

void URegisterWidget::OnRegisterButtonClicked()
{
	//Clear Error Text
	ErrorText->SetText(FText());
	
	if (UFormFieldsValidatorLib::IsRegisterFieldsValid(LoginText->GetText(), NicknameText->GetText(),
	                                                   EmailText->GetText(), PasswordText->GetText(),
	                                                   ConfirmPasswordText->GetText()))
	{
		FRegisterRequest RegisterRequest;
		RegisterRequest.Login = GetStringValueFromEditableTextBox(LoginText);
		RegisterRequest.Nickname = GetStringValueFromEditableTextBox(NicknameText);
		RegisterRequest.Email = GetStringValueFromEditableTextBox(EmailText);
		RegisterRequest.Password = GetStringValueFromEditableTextBox(PasswordText);
		
		UHTTPGameAPIRequestsLib::GameAPIRegisterRequest([this](const bool bSuccess, const FRegisterResponse& RegisterResponse, const FErrorResponse& RegisterErrorResponse)
		{
			if (bSuccess)
			{
				UE_LOG(LogTemp, Warning, TEXT("Register success!"));
				OnFormExecute.Broadcast(RegisterResponse.Token);
			}
			else
			{
				ErrorText->SetText(FText::FromString(RegisterErrorResponse.Error));
			}
			
		},RegisterRequest);
	}
	else
	{
		ErrorText->SetText(FText::FromString("Invalid register fields!"));
	}
	
}

FString URegisterWidget::GetStringValueFromEditableTextBox(UEditableTextBox* EditableTextBox) const 
{
	FString StringValue = EditableTextBox->GetText().ToString();
	return StringValue;
}
