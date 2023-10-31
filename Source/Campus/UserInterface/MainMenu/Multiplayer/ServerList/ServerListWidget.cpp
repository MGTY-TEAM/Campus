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
	M_UpdateServerListButton->OnClicked.AddDynamic(this, &UServerListWidget::OnUpdateServerListButtonClicked);

	M_UserGameInstance = Cast<UUserGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (M_UserGameInstance)
	{
		M_UserGameInstance->OnSearchComplete.BindUObject(this, &UServerListWidget::OnSearchComplete);
	}
}

void UServerListWidget::OnUpdateServerListButtonClicked()
{
	
}

void UServerListWidget::OnSearchComplete(TArray<FOnlineSessionSearchResult> OnlineSessionSearchResults)
{
	M_ServersVerticalBox->ClearChildren();
	
	if (OnlineSessionSearchResults.Num())
	{
		for (FOnlineSessionSearchResult SessionSearchResult : OnlineSessionSearchResults)
		{
			if (SessionSearchResult.IsValid() && SessionSearchResult.IsSessionInfoValid())
			{
				SessionSearchResult.Session.
			}
		}
	}
}


