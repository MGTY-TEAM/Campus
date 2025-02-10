// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TimerManager.h"
#include "../AI/AIDrone/DroneGuide.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "ChatBox.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTeleportationDelegate, int, index);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDarkeningDelegate);


UCLASS()
class CAMPUS_API UChatBox : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget")
	TSubclassOf<UUserWidget> BlueprintWidgetClass;

	ADroneGuide* Drone;

	bool bCanRobotMoveToLocation = false;
	
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* ParentPanel;
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* ChatBox_Panel;
	
	UPROPERTY(meta = (BindWidget))
	class UImage* ChatBar_BG;
	UPROPERTY(meta = (BindWidget))
	class UImage* ChatIcon;
	UPROPERTY(meta = (BindWidget))
	class UImage* Chat_BG;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* SendMessage_TextBox;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* SendMessage_Button;

	UPROPERTY(meta = (BindWidget))
	class UScrollBox* Chat_ScrollBox;

	UPROPERTY(BlueprintAssignable, Category="Dispatcher")
	FTeleportationDelegate TeleportationEvent;

	UPROPERTY(BlueprintAssignable, Category="Dispatcher")
	FDarkeningDelegate DarkeningEvent;

	FTimerHandle TeleportTimer;
	FTimerDelegate TimerDel;

	void StartTeleport(int index);
	
protected:
	UFUNCTION()
	virtual bool Initialize();

	UFUNCTION()
	virtual void NativeConstruct() override;

	UFUNCTION()

	
	void SendMessageButtonClicked();

	//UFUNCTION()
	//void OnTextBoxTextCommitted(const FText& Text, ETextCommit::Type CommitMethod);

	void SendMessage(FText Message, FText Sender);

	void BotResponse(const FString& Message, const FString& ActionType, const int& ActionID);

	
};

