// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Chat_Message.generated.h"

/**
 * 
 */
UCLASS()
class CAMPUS_API UChat_Message : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* ParentPanel;

	UPROPERTY(meta = (BindWidget))
	class UHorizontalBox* ChatMessage_Box;
public:
	
	UPROPERTY(meta = (BindWidget), EditAnywhere)
	class UTextBlock* Sender;
	UPROPERTY(meta = (BindWidget), EditAnywhere)
	class UTextBlock* Message;
};
