// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Campus/Chat/ChatUserComponent.h"
#include "GameFramework/HUD.h"
#include "BaseHUD.generated.h"

DECLARE_LOG_CATEGORY_CLASS(BaseHUDLog, Log, Log);

class UChatBox;
/**
 * 
 */
UCLASS()
class CAMPUS_API ABaseHUD : public AHUD
{
	GENERATED_BODY()
public:
	
	void SwitchChatState();
	void SwitchEscapeMenuState();
	
	void SetupChat(UChatUserComponent* ChatUserComponent);
protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "UI Classes")
	TSubclassOf<UChatBox> ChatBoxClass;
	UChatBox* ChatBox;

	UPROPERTY(EditDefaultsOnly, Category = "UI Classes")
	TSubclassOf<UUserWidget> CrosshairClass;
	UUserWidget* Crosshair;

	UPROPERTY(EditDefaultsOnly, Category = "UI Classes")
	TSubclassOf<UUserWidget> EscapeMenuClass;
	UUserWidget* EscapeMenu;
	
	
	virtual void DrawHUD() override;
	virtual void AddCrosshair();
	
	virtual void BeginPlay() override;
	
};
