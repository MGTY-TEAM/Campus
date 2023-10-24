// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInfoWidget.h"

#include "Campus/Core/UserGameInstance.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UUserInfoWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	UUserGameInstance* GameInstance = Cast<UUserGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GameInstance)
	{
		NicknameText->SetText(FText::FromString(GameInstance->GetNickname()));
		EmailText->SetText(FText::FromString(GameInstance->GetEmail()));
	}
}
