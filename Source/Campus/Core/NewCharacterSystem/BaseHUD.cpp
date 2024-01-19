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
		if (ChatBox->IsInViewport())
		{
			ChatBox->RemoveFromParent();
		}
		else
		{
			ChatBox->AddToViewport();
			
			ChatBox->SetFocusOnTextInput();
		}
	}*/
}

void ABaseHUD::SwitchEscapeMenuState()
{
	
}



void ABaseHUD::SetupChat(UChatUserComponent* ChatUserComponent)
{
	if (!ChatBox)
	{
		ChatBox = Cast<UChatBox>(CreateWidget(GetWorld(), ChatBoxClass));
		ChatBox->AddToViewport();
		ChatBox->ConnectChatComponent(ChatUserComponent);
	}
}


void ABaseHUD::AddCrosshair()
{
	Crosshair = CreateWidget(GetWorld(), CrosshairClass);
	if (Crosshair)
	{
		Crosshair->AddToPlayerScreen();
		UE_LOG(BaseHUDLog, Log, TEXT("Crosshair Succesfully Added"));
	}
}
