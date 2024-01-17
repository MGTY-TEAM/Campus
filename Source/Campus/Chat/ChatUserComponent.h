// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Campus/Chat/MessageInstance.h"
#include "Components/ActorComponent.h"
#include "ChatUserComponent.generated.h"

DECLARE_DELEGATE_OneParam(FOnMessageReceived, UMessageInstance*)

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CAMPUS_API UChatUserComponent : public UActorComponent
{
	GENERATED_BODY()
	
	FName UserID;
	
public:
	UChatUserComponent();

	FOnMessageReceived OnMessageReceived;

	void SetUserID(const FName& NewUserID);
	
	virtual void ReceiveMessage(UMessageInstance* MessageInstance);
	virtual void SendMessage(const FName& ReceiverID, const FText& Message);
};
