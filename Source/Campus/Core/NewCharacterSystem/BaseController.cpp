// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseController.h"

#include "BaseHUD.h"
#include "Campus/Chat/ChatManager.h"
#include "LocalComponents/InteractionComponent.h"

ABaseController::ABaseController()
{
	ChatUserComponent = CreateDefaultSubobject<UChatUserComponent>("ChatUserComponent");

	UChatManager& ChatManager = UChatManager::Get();
	ChatUserComponent->SetUserID("DefaultCharacterName");
	if (ChatManager.RegisterUser("DefaultCharacterName", ChatUserComponent)){}
	
	if (ABaseHUD* BaseHUD = Cast<ABaseHUD>(MyHUD))
	{
		BaseHUD->SetupChat(ChatUserComponent);	
	}
}

void ABaseController::BeginPlay()
{
	Super::BeginPlay();
	
	SetInputMode(FInputModeGameAndUI());
}

void ABaseController::OnChatButtonClicked()
{
	if(ABaseHUD* BaseHUD = Cast<ABaseHUD>(MyHUD))
	{
		BaseHUD->SwitchChatState();
	}
}

void ABaseController::OnEscapeMenuButtonClicked()
{
	if (ABaseHUD* BaseHUD = Cast<ABaseHUD>(MyHUD))
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
