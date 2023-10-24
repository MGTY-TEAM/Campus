// Fill out your copyright notice in the Description page of Project Settings.


#include "UserGameInstance.h"

#include "Kismet/GameplayStatics.h"
#include "../Libraries/Requests/GameAPI/HTTPGameAPIRequestsLib.h"
#include "../Libraries/Requests/GameAPI/HTTPGameAPIStructures.h"


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
		[this](const bool& bSuccess, const FUserInfoResponse& UserInfoResponse, const FErrorResponse& UserInfoErrorResponse)
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

bool UUserGameInstance::TryConnectToGameServerAndOpenMultiplayerMap(const FString& Port)
{
	if (!Port.IsEmpty())
	{
		M_GameServerPort = Port;
		UGameplayStatics::OpenLevel(this, "L_MultiplayerSession");
		return true;
	}
	return false;
}


