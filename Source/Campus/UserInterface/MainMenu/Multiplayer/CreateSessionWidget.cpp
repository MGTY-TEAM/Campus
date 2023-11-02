// Fill out your copyright notice in the Description page of Project Settings.


#include "CreateSessionWidget.h"

#include "Campus/Core/UserGameInstance.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Kismet/GameplayStatics.h"


void UCreateSessionWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	CreateSessionButton->OnClicked.AddDynamic(this, &UCreateSessionWidget::OnCreateSessionButtonClicked);
}

void UCreateSessionWidget::OnCreateSessionButtonClicked()
{
	UUserGameInstance* UserGameInstance = Cast<UUserGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (UserGameInstance)
	{
		UserGameInstance->CreateSession(FName(SessionNameField->GetText().ToString()));
	}
}