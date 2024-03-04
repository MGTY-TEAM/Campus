// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatManager.h"

#include "MessageInstance.h"
#include "Components/ChatUserComponent.h"


UChatManager* UChatManager::ChatManagerInstance = nullptr;

UChatManager::UChatManager(){}

UChatManager* UChatManager::Get()
{
	if (!ChatManagerInstance)
	{
		ChatManagerInstance = NewObject<UChatManager>();
		ChatManagerInstance->AddToRoot();
	}
	return ChatManagerInstance;
}

void UChatManager::BeginDestroy()
{
	Super::BeginDestroy();
	
	if (ChatManagerInstance)
	{
		ChatManagerInstance->RemoveFromRoot();
		ChatManagerInstance = nullptr;
	}
}


bool UChatManager::RegisterUser(const FName& UserID, UChatUserComponent* User)
{
	if (!UserID.IsNone() && !ValidateUserID(UserID) && User)
	{
		RegisteredUsers.Add(UserID, User);
#ifdef CHAT_MANAGER_DEBUG
		UE_LOG(LogChatManager, Log, TEXT("User registered : %s"), *UserID.ToString());
#endif
		return true;
	}
	return false;
}

bool UChatManager::ValidateUserID(const FName& UserID) const 
{
	return RegisteredUsers.Contains(UserID);
}

void UChatManager::SendChatMessage(const FName& SenderID, const FName& ReceiverID, const FText& Message)
{
	if (ValidateUserID(SenderID) && ValidateUserID(ReceiverID))
	{
		UMessageInstance* NewMessage = NewObject<UMessageInstance>();
		NewMessage->SetupMessage(SenderID, ReceiverID, Message);

		UChatUserComponent* Receiver = RegisteredUsers[ReceiverID];
		if (Receiver)
		{
#ifdef CHAT_MANAGER_DEBUG
			UE_LOG(LogChatManager, Log, TEXT("Message transmission"));
#endif
			Receiver->ReceiveMessage(NewMessage);
		}
	}
}


