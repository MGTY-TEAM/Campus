// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerItemWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"



void UServerItemWidget::SetServerItemInfo(const FString& MaxPlayersCount, const FString& PlayersCount,
										  const FString& SessionID, const FString& SessionPing)
{
	PlayersCountText->SetText(FText::FromString(PlayersCount));
	MaxPlayersCountText->SetText(FText::FromString(MaxPlayersCount));
	SessionIDText->SetText(FText::FromString(SessionID));
	PingText->SetText(FText::FromString(SessionPing));
}

void UServerItemWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ConnectButton->OnClicked.AddDynamic(this, &UServerItemWidget::OnButtonClicked);
}

void UServerItemWidget::OnButtonClicked()
{
	OnConnectButtonClicked.Execute(SessionIDText->GetText().ToString());
}

