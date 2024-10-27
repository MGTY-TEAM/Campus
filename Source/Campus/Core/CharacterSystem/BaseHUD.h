// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Campus/Chat/Components/ChatUserComponent.h"
#include "GameFramework/HUD.h"
#include "BaseHUD.generated.h"

class IQuestsAssigner;
class UQuestViewController;
class UInteractionWidget;
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

	UFUNCTION(BlueprintCallable)
	void AddExternalQuestView(UObject* QuestsView);
protected:
	UPROPERTY(EditDefaultsOnly, Category = "UI Classes")
	TSubclassOf<UChatBox> ChatBoxClass;
	UChatBox* ChatBox;

	UPROPERTY(EditDefaultsOnly, Category= "UI Classes")
	TSubclassOf<UInteractionWidget> InteractionWidgetClass;
	UInteractionWidget* InteractionWidget;
	
	UPROPERTY(EditDefaultsOnly, Category = "UI Classes")
	TSubclassOf<UUserWidget> CrosshairClass;
	UUserWidget* Crosshair;

	UPROPERTY(EditDefaultsOnly, Category = "UI Classes")
	TSubclassOf<UUserWidget> EscapeMenuClass;
	UUserWidget* EscapeMenu;

	UPROPERTY(EditDefaultsOnly, Category = "UI Classes")
	TSubclassOf<UUserWidget> SimpleQuestViewClass;
	TWeakObjectPtr<UUserWidget> SimpleQuestView;

	TWeakObjectPtr<UQuestViewController> QuestViewController;
	
	virtual void DrawHUD() override;
	
	virtual void AddCrosshair();
	
	virtual void AddSimpleQuestView();
	
	void AddInteractionWidget();
	
	virtual void PostLoad() override;
	
	virtual void BeginPlay() override;
	
};
