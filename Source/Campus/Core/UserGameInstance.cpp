﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "UserGameInstance.h"

#include "Kismet/GameplayStatics.h"
#include "../Libraries/Requests/GameAPI/HTTPGameAPIRequestsLib.h"
#include "../Libraries/Requests/GameAPI/HTTPGameAPIStructures.h"
#include "Campus/IncentiveSystem/QuestSystem/QuestManager.h"
#include "Campus/IncentiveSystem/QuestSystem/Data/QuestRowBase.h"

void UUserGameInstance::Init()
{
	Super::Init();
	Quests = TArray<UQuest*>();
}

void UUserGameInstance::LoadComplete(const float LoadTime, const FString& MapName)
{
	Super::LoadComplete(LoadTime, MapName);

	if(Quests.IsEmpty())
	{
		if(QuestTable)
		{
			TArray<FQuestRowBase*> QuestRows;
			QuestTable->GetAllRows("", QuestRows);

			UQuestManager::FillQuestsByData(QuestRows);

			TArray<TWeakObjectPtr<UQuest>> WeakQuests = UQuestManager::GetQuests();

			for(TWeakObjectPtr<UQuest> WeakQuest : WeakQuests)
			{
				if(WeakQuest.IsValid())
				{
					Quests.Add(WeakQuest.Get());
				}
			}
		}
	}
	else
	{
		UQuestManager::FillQuests(Quests);
	}
}

void UUserGameInstance::Shutdown()
{
	Super::Shutdown();
}

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

void UUserGameInstance::SetUserToken(const FString& Token)
{
	if (M_UserToken.IsEmpty())
	{
		M_UserToken = Token;
	}
}

bool UUserGameInstance::TryToGetAndFillUserInfoAndTransitToMainMenu()
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
#ifdef USER_GAME_INSTANCE_DEBUG
				UE_LOG(LogUserGameInstance, Log, TEXT("User info is filled. UserID: %s"), *UserInfoResponse.UserID);
#endif
#ifdef USER_GAME_INSTANCE_DEBUG
				UE_LOG(LogUserGameInstance, Log, TEXT("Transit to main menu level"))
#endif
				UGameplayStatics::OpenLevel(this, "L_MainMenu");
				return true;
			}
			return false;
		}, UserInfoRequest);
	return false;
}



