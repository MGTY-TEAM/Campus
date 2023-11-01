// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerListWidget.h"

#include "ServerItemWidget.h"
#include "Campus/Core/UserGameInstance.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "Kismet/GameplayStatics.h"


void UServerListWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	UpdateServerListButton->OnClicked.AddDynamic(this, &UServerListWidget::OnUpdateServerListButtonClicked);

	M_UserGameInstance = Cast<UUserGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (M_UserGameInstance)
	{
		M_UserGameInstance->OnSearchComplete.BindUObject(this, &UServerListWidget::OnSearchComplete);
	}
}

void UServerListWidget::OnUpdateServerListButtonClicked()
{
	if (M_UserGameInstance)
	{
		M_UserGameInstance->FindSessions();
	}

}

void UServerListWidget::OnServerButtonClicked(const FString& SessionId)
{
	if (M_UserGameInstance)
	{
		M_UserGameInstance->JoinSession(TODO);
	}

}

void UServerListWidget::OnSearchComplete(TArray<FOnlineSessionSearchResult> OnlineSessionSearchResults)
{
	ServersVerticalBox->ClearChildren();

	if (OnlineSessionSearchResults.Num())
	{
		for (FOnlineSessionSearchResult SessionSearchResult : OnlineSessionSearchResults)
		{
			if (SessionSearchResult.IsValid() && SessionSearchResult.IsSessionInfoValid())
			{
				UServerItemWidget* ItemWidget = CreateWidget<UServerItemWidget>(this, ServerItemWidgetClass);
				ItemWidget->SetServerItemInfo(FString::FromInt(SessionSearchResult.Session.NumOpenPublicConnections),
				                              FString::FromInt(SessionSearchResult.Session.NumOpenPrivateConnections),
				                              SessionSearchResult.Session.GetSessionIdStr(),
				                              FString::FromInt(SessionSearchResult.PingInMs));
				
				ItemWidget->OnConnectButtonClicked.BindUObject(this, &UServerListWidget::OnServerButtonClicked);
				ServersVerticalBox->AddChild(ItemWidget);
			}
		}
	}
}

