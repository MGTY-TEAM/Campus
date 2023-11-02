// Fill out your copyright notice in the Description page of Project Settings.


#include "UserGameInstance.h"

#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Online/OnlineSessionNames.h"
#include "Kismet/GameplayStatics.h"
#include "../Libraries/Requests/GameAPI/HTTPGameAPIRequestsLib.h"
#include "../Libraries/Requests/GameAPI/HTTPGameAPIStructures.h"
#include "GameFramework/PlayerState.h"


const FString& UUserGameInstance::GetUserID() const
{
	return M_UserInfo.ID;
}

const FString& UUserGameInstance::GetUserToken() const
{
	return M_UserToken;
}

const FString& UUserGameInstance::GetNickname() const
{
	return M_UserInfo.Nickname;
}

const FString& UUserGameInstance::GetEmail() const
{
	return M_UserInfo.Email;
}

const FString& UUserGameInstance::GetGameServerPort() const
{
	return M_GameServerPort;
}

void UUserGameInstance::SetUserToken(const FString& Token)
{
	if (M_UserToken.IsEmpty())
	{
		M_UserToken = Token;
	}
}

bool UUserGameInstance::TryToGetAndFillUserInfoAndOpenMainMenu()
{
	FUserInfoRequest UserInfoRequest;
	UserInfoRequest.Token = GetUserToken();
	UHTTPGameAPIRequestsLib::GameAPIUserInfoRequest(
		[this](const bool& bSuccess, const FUserInfoResponse& UserInfoResponse,
		       const FErrorResponse& UserInfoErrorResponse)
		{
			if (bSuccess)
			{
				M_UserInfo.Email = UserInfoResponse.Email;
				M_UserInfo.Nickname = UserInfoResponse.Nickname;
				M_UserInfo.ID = UserInfoResponse.UserID;

				UE_LOG(LogTemp, Warning, TEXT("User info is filled. UserID: %s"), *UserInfoResponse.UserID);

				UGameplayStatics::OpenLevel(this, "L_MainMenu");
				return true;
			}
			return false;
		}, UserInfoRequest);

	return false;
}

void UUserGameInstance::Init()
{
	if (IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get())
	{
		M_SessionInterface = Subsystem->GetSessionInterface();
		if (M_SessionInterface.IsValid())
		{
			M_SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UUserGameInstance::OnSessionCreated);
			M_SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UUserGameInstance::OnSessionsFind);
			M_SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UUserGameInstance::OnJoinSessionComplete);
		}
	}
}

void UUserGameInstance::CreateSession(const FName& SessionName)
{
	UE_LOG(LogSession, Warning, TEXT("CreateSession"))
	if (M_SessionInterface)
	{
		M_SessionInterface->DestroySession(FName("My Session"));
		FOnlineSessionSettings SessionSettings;
		SessionSettings.bAllowJoinInProgress = true;
		SessionSettings.bIsDedicated = false;
		SessionSettings.bIsLANMatch = true;
		SessionSettings.bUsesPresence = true;
		SessionSettings.bShouldAdvertise = true;
		SessionSettings.NumPublicConnections = 25;

		SessionSettings.Set(FName("SERVER_NAME_KEY"), SessionName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

		M_SessionInterface->CreateSession(0, SessionName, SessionSettings);
	}
}

void UUserGameInstance::JoinSession(const FName& SessionName, FOnlineSessionSearchResult SearchResult)
{
	UE_LOG(LogSession, Warning, TEXT("JoinSession"))
	if (M_SessionInterface)
	{
		M_SessionInterface->JoinSession(0, SessionName, SearchResult);
	}
}

void UUserGameInstance::FindSessions()
{
	if (M_SessionInterface)
	{
		SessionSearch = MakeShareable(new FOnlineSessionSearch());
		SessionSearch->bIsLanQuery = true;
		SessionSearch->MaxSearchResults = 10000;
		SessionSearch->QuerySettings.Set(SEARCH_PRESENCE,true, EOnlineComparisonOp::Equals);
		M_SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
	}
}

void UUserGameInstance::OnSessionCreated(FName SessionName, bool Succeeded)
{
	UE_LOG(LogSession, Warning, TEXT("OnCreateSessionComplete, Succeded: %d"), Succeeded);
	
	if (Succeeded)
	{
		UE_LOG(LogSession, Warning, TEXT("Join Sesssion"))
		GetWorld()->ServerTravel("/Game/Levels/L_MultiplayerMap?listen");
	}
}

void UUserGameInstance::OnSessionsFind(bool Succeeded)
{
	UE_LOG(LogSession, Warning, TEXT("OnFindSessionComplete, Succeded: %d"), Succeeded);
	if (Succeeded)
	{
		TArray<FOnlineSessionSearchResult> SearchResults = SessionSearch->SearchResults;
		UE_LOG(LogSession, Warning, TEXT("SearchResults, Server Count: %d"), SearchResults.Num());
		if (SearchResults.Num())
		{
			OnSearchComplete.Execute(SearchResults);
			
		}
	}
}

void UUserGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	UE_LOG(LogSession, Warning, TEXT("OnJoinSessionComplete"))

	if (APlayerController* PController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		FString JoinAddress = "";
		M_SessionInterface->GetResolvedConnectString(SessionName, JoinAddress);
		if (!JoinAddress.IsEmpty())
		{
			JoinAddress;  
			PController->ClientTravel(JoinAddress, TRAVEL_Absolute);
		}
	}
}
