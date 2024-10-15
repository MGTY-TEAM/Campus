// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseController.h"

#include "BaseHUD.h"
#include "EnhancedInputSubsystems.h"
#include "Campus/Chat/ChatManager.h"

ABaseController::ABaseController()
{
#ifdef BASE_CONTROLLER_DEBUG
	UE_LOG(LogBaseController, Log, TEXT("Add chat user component"));
#endif
	M_ChatUserComponent = CreateDefaultSubobject<UChatUserComponent>("ChatUserComponent");
}

void ABaseController::BeginPlay()
{
	Super::BeginPlay();
	
	SetInputMode(FInputModeGameOnly());
	
	M_ChatUserComponent->SetUserID("DefaultCharacterName");
	
#ifdef BASE_CONTROLLER_DEBUG
	UE_LOG(LogBaseController, Log, TEXT("Try to register"));
#endif
	
	UChatManager::Get()->RegisterUser("DefaultCharacterName", M_ChatUserComponent);

	if (MyHUD)
	{
#ifdef BASE_CONTROLLER_DEBUG
		UE_LOG(LogBaseController, Log, TEXT("Try get HUD"));
#endif
		M_BaseHUD = Cast<ABaseHUD>(MyHUD);
		if (M_BaseHUD)
		{
#ifdef BASE_CONTROLLER_DEBUG
			UE_LOG(LogBaseController, Log, TEXT("Try to setup chat"));
#endif
			M_BaseHUD->SetupChat(M_ChatUserComponent);
		}
	}

}

void ABaseController::SpawnDefaultHUD()
{
	Super::SpawnDefaultHUD();
}

void ABaseController::SetupInputComponent()
{
	Super::SetupInputComponent();

}

void ABaseController::SetupPCInputContext()
{
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(PCMappingContext, 0);
	}
}

void ABaseController::SetupVRInputContext()
{
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(VRMappingContext, 0);
	}
}
