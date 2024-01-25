// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ChatManager.generated.h"

DECLARE_LOG_CATEGORY_CLASS(LogChatManager, Log, Log);
class UChatUserComponent;
/**
 * 
 */
UCLASS()
class CAMPUS_API UChatManager : public UObject
{
	GENERATED_BODY()

	static TMap<FName, UChatUserComponent*> RegisteredUsers;
	static bool ValidateUserID(const FName& UserID);
	
public:
	
	static bool RegisterUser(const FName& UserID, UChatUserComponent* User);

	static void SendChatMessage(const FName& SenderID, const FName& ReceiverID, const FText& MessageContent);
	static TArray<FName> GetUserListWithoutSelf(const FName& SelfUserID);
};
