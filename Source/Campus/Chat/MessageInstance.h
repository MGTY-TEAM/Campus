// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MessageInstance.generated.h"

/**
 * 
 */
UCLASS()
class CAMPUS_API UMessageInstance : public UObject
{
	GENERATED_BODY()

	FName SenderID;
	FName ReceiverID;
	FText Message;
public:
	
	TTuple<FName, FName, FText> GetMessageInfo();
	
	void SetupMessage(const FName& NewSenderID, const FName& NewReceiverID, const FText& NewMessage);
};
