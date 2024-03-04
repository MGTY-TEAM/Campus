// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatUserComponent.h"

#include "Campus/Chat/MessageInstance.h"
#include "Campus/Chat/ChatManager.h"


UChatUserComponent::UChatUserComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UChatUserComponent::SetUserID(const FName& UserID)
{
#ifdef CHAT_USER_COMPONENT_DEBUG
	UE_LOG(LogChatUserComponent, Warning, TEXT("User id registered: %s"), *UserID.ToString());
#endif
	M_UserID = UserID;
}

void UChatUserComponent::ReceiveMessage(UMessageInstance* MessageInstance)
{
#ifdef CHAT_USER_COMPONENT_DEBUG
	UE_LOG(LogChatUserComponent, Log, TEXT("Recive chat message"))
#endif
	MessageInstance->GetMessageInfo();
	OnMessageReceived.Broadcast(MessageInstance);
}

void UChatUserComponent::SendMessage(const FName& ReceiverID, const FText& Message)
{
#ifdef CHAT_USER_COMPONENT_DEBUG
	UE_LOG(LogChatUserComponent, Log, TEXT("Send chat message"))
#endif
	UChatManager::Get()->SendChatMessage(M_UserID, ReceiverID, Message);
}


