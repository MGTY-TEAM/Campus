// Fill out your copyright notice in the Description page of Project Settings.


#include "MessageInstance.h"

TTuple<FName, FName, FText> UMessageInstance::GetMessageInfo()
{
	TTuple<FName, FName, FText> Info = TTuple<FName, FName, FText>(SenderID, ReceiverID, Message);
	return Info;
}

void UMessageInstance::SetupMessage(const FName& NewSenderID, const FName& NewReceiverID, const FText& NewMessage)
{
	SenderID = NewSenderID;
	ReceiverID = NewReceiverID;
	Message = NewMessage;
}
