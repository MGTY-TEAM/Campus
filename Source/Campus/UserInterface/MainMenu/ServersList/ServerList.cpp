// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerList.h"
#include "ServerItem.h"
#include "Campus/Core/UserGameInstance.h"
#include "Campus/Libraries/Requests/GameAPI/HTTPGameAPIRequestsLib.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "Kismet/GameplayStatics.h"


class UUserGameInstance;

void UServerList::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	UpdateServerListButton->OnClicked.AddDynamic(this, &UServerList::UpdateServerListButtonClicked);
}

void UServerList::UpdateServerListButtonClicked()
{
	UHTTPGameAPIRequestsLib::GameApiServerInfoRequest([this](const bool& bSuccess, const TArray<FServerInfo>& ServerInfos, const FErrorResponse&)
	{
		if (bSuccess)
		{
			for (auto ServerInfo : ServerInfos)
			{
				bool bContains = false;
				for (auto ServerItem: ServerItemList)
				{
					if (ServerInfo.Port == ServerItem->GetPort())
					{
						ServerItem->UpdateClientsCount(ServerInfo.ConnectedClients);
						bContains = true;
					}
				}
				if (!bContains)
				{
					UServerItem* ServerItem = CreateWidget<UServerItem>(GetWorld(), ServerItemClass);
					
					ServerItem->SetInfo(ServerInfo.Port, ServerInfo.ConnectedClients);
					ServerItem->OnFormExecute.AddDynamic(this, &UServerList::OnConnectButtonClicked);
					
					ServerItemList.Add(ServerItem);
					ServerListBox->AddChild(ServerItem);
					
				}
			}

		}
	});
}

void UServerList::OnConnectButtonClicked(const FString& Port)
{
	UUserGameInstance* GameInstance  = Cast<UUserGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GameInstance)
	{
		GameInstance->TryConnectToGameServerAndOpenMultiplayerMap(Port);
	}
}
