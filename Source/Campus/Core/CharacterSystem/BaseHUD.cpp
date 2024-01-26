// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseHUD.h"

#include "Blueprint/UserWidget.h"
#include "Campus/UserInterface/ChatBox.h"


void ABaseHUD::DrawHUD()
{
	Super::DrawHUD();
}

void ABaseHUD::BeginPlay()
{
	Super::BeginPlay();
	AddCrosshair();
}

void ABaseHUD::SwitchChatState()
{
	/*if (ChatBox)
	{
		if (!ChatBox->bIsFocusable)
		{
			ChatBox->RemoveFromParent();
		}
		else
		{
			ChatBox->AddToViewport();
			
			ChatBox->SetFocus();
		}
	}*/
}

void ABaseHUD::SwitchEscapeMenuState()
{
}


void ABaseHUD::SetupChat(UChatUserComponent* ChatUserComponent)
{
	if (UChatBox* NewChatBox = CreateWidget<UChatBox>(GetWorld(), ChatBoxClass))
	{
		ChatBox = NewChatBox;
		ChatBox->AddToPlayerScreen(1);
		ChatBox->ConnectChatComponent(ChatUserComponent);
		UE_LOG(LogTemp, Error, TEXT("%"), *ChatBox->GetName())
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
