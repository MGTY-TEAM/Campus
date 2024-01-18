// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseController.h"

#include "BaseHUD.h"
#include "Campus/Chat/ChatManager.h"
#include "LocalComponents/InteractionComponent.h"

ABaseController::ABaseController()
{
	ChatUserComponent = CreateDefaultSubobject<UChatUserComponent>("ChatUserComponent");
	if (ChatUserComponent)
	{
		ChatUserComponent->SetUserID("DefaultCharacterName");
	}
}

void ABaseController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeGameOnly());

	
	if (ChatUserComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Chat user component "));
		if (UChatManager::RegisterUser("DefaultCharacterName", ChatUserComponent))
		{
			UE_LOG(LogTemp, Warning, TEXT("User Registered"));
			if (MyHUD)
			{
				BaseHUD = Cast<ABaseHUD>(MyHUD);
				BaseHUD->SetupChat(ChatUserComponent);

				UE_LOG(LogTemp, Warning, TEXT("Setup Hud"));
			}
		}
		
	}
}


void ABaseController::SpawnDefaultHUD()
{
	Super::SpawnDefaultHUD();
}

void ABaseController::OnChatButtonClicked()
{
	if (BaseHUD)
	{
		BaseHUD->SwitchChatState();

		UE_LOG(LogTemp, Warning, TEXT("BaseHudSwitch"));
	}
}

void ABaseController::OnEscapeMenuButtonClicked()
{
	if (BaseHUD)
	{
		BaseHUD->SwitchEscapeMenuState();
	}
}

void ABaseController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("OpenChat", IE_Pressed, this, &ABaseController::OnChatButtonClicked);
	InputComponent->BindAction("OpenEscapeMenu", IE_Pressed, this, &ABaseController::OnEscapeMenuButtonClicked);
}
