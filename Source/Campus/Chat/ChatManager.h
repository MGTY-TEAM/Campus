// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ChatManager.generated.h"

class UChatUserComponent;
/**
 * 
 */
UCLASS()
class CAMPUS_API UChatManager : public UObject
{
	GENERATED_BODY()
	
	UChatManager();
	
	TMap<FName, UChatUserComponent*> RegisteredUsers;
public:
	static UChatManager& Get();
	
	bool RegisterUser(const FName& UserID, UChatUserComponent* User);
	bool ValidateUserID(const FName& UserID) const;
	void SendChatMessage(const FName& SenderID, const FName& ReceiverID, const FText& MessageContent);
	TArray<FName> GetUserListWithoutSelf(const FName& SelfUserID) const;
};
