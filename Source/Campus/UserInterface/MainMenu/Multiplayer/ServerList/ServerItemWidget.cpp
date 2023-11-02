// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerItemWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"



void UServerItemWidget::SetServerItemInfo(const FString& MaxPlayersCount, const FString& PlayersCount,
										  const FString& SessionID, const FString& SessionPing, FOnlineSessionSearchResult SessionSearchResult)
{
	PlayersCountText->SetText(FText::FromString(PlayersCount));
	MaxPlayersCountText->SetText(FText::FromString(MaxPlayersCount));
	PingText->SetText(FText::FromString(SessionPing));

	FString SessionName;
	SessionSearchResult.Session.SessionSettings.Get("SERVER_NAME_KEY",SessionName);

	SessionIDText->SetText(FText::FromString(SessionName));
}

void UServerItemWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ConnectButton->OnClicked.AddDynamic(this, &UServerItemWidget::OnButtonClicked);
}

void UServerItemWidget::OnButtonClicked()
{
	OnConnectButtonClicked.Execute(SessionSearchResult);
}

