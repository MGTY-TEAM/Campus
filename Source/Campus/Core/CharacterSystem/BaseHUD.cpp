// Fill out your copyright notice in the Description page of Project Settings.
#include "BaseHUD.h"

#include "Blueprint/UserWidget.h"
#include "Campus/IncentiveSystem/QuestSystem/QuestsAssigner.h"
#include "Campus/IncentiveSystem/QuestSystem/QuestViewController.h"
#include "Campus/UserInterface/ChatBox.h"
#include "Campus/UserInterface/Hud/Interaction/InteractionWidget.h"

void ABaseHUD::DrawHUD()
{
	Super::DrawHUD();
}

void ABaseHUD::BeginPlay()
{
	Super::BeginPlay();
	AddCrosshair();
	AddInteractionWidget();
	QuestViewController = NewObject<UQuestViewController>();
	AddSimpleQuestView();
}

void ABaseHUD::AddInteractionWidget()
{
	if(UInteractionWidget* NewInteractionWidget = CreateWidget<UInteractionWidget>(GetWorld(), InteractionWidgetClass))
	{
		InteractionWidget = NewInteractionWidget;

		UE_LOG(BaseHUDLog, Warning, TEXT("InteractionWidget added to viewport"));
		InteractionWidget->AddToViewport();
	}
}

void ABaseHUD::SwitchChatState(){}

void ABaseHUD::SwitchEscapeMenuState(){}

void ABaseHUD::SetupChat(UChatUserComponent* ChatUserComponent)
{
	if (UChatBox* NewChatBox = CreateWidget<UChatBox>(GetWorld(), ChatBoxClass))
	{
		ChatBox = NewChatBox;
		ChatBox->AddToPlayerScreen(1);
		ChatBox->ConnectChatComponent(ChatUserComponent);
		UE_LOG(LogTemp, Log, TEXT("%"), *ChatBox->GetName())
	}
}

void ABaseHUD::AddCrosshair()
{
	Crosshair = CreateWidget(GetWorld(), CrosshairClass);
	if (Crosshair)
	{
		Crosshair->AddToViewport();
		UE_LOG(BaseHUDLog, Log, TEXT("Crosshair Succesfully Added"));
	}
}

void ABaseHUD::AddSimpleQuestView()
{
	SimpleQuestView = CreateWidget(GetWorld(), SimpleQuestViewClass);
	if(SimpleQuestView)
	{
		SimpleQuestView->AddToViewport();
		UE_LOG(BaseHUDLog, Log, TEXT("Simple quest view succesfully added"));
		if(QuestViewController)
		{
			if(SimpleQuestView->GetClass()->ImplementsInterface(UQuestsAssigner::StaticClass()))
			{
				QuestViewController->AddQuestView(SimpleQuestView);
			}
		}
	}
}
