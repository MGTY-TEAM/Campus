// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatUserComponent.h"

#include "Campus/Chat/MessageInstance.h"
#include "Campus/Chat/ChatManager.h"


// Sets default values for this component's properties
UChatUserComponent::UChatUserComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UChatUserComponent::SetUserID(const FName& NewUserID)
{
	UserID = NewUserID;
}

void UChatUserComponent::ReceiveMessage(UMessageInstance* MessageInstance)
{
	MessageInstance->GetMessageInfo();
	OnMessageReceived.Execute(MessageInstance);
}

void UChatUserComponent::SendMessage(const FName& ReceiverID, const FText& Message)
{
	UChatManager::SendChatMessage(UserID, ReceiverID, Message);
}


