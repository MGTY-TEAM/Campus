// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatManager.h"

#include "MessageInstance.h"
#include "ChatUserComponent.h"

TMap<FName, UChatUserComponent*> UChatManager::RegisteredUsers = TMap<FName, UChatUserComponent*>();

bool UChatManager::RegisterUser(const FName& UserID, UChatUserComponent* User)
{
	if (!UserID.IsNone() && !ValidateUserID(UserID) && User)
	{
		RegisteredUsers.Add(UserID, User);
		return true;
	}
	return false;
}

bool UChatManager::ValidateUserID(const FName& UserID) 
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
			Receiver->ReceiveMessage(NewMessage);
		}
	}
}

TArray<FName> UChatManager::GetUserListWithoutSelf(const FName& SelfUserID) 
{
	TArray<FName> UserID;
	RegisteredUsers.GetKeys(UserID);
	return UserID;
}
