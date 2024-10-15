// Fill out your copyright notice in the Description page of Project Settings.

#include "SinglePlayerGameMode.h"

#include "EnhancedInputSubsystems.h"
#include "IHeadMountedDisplay.h"
#include "IXRTrackingSystem.h"
#include "Campus/Core/CharacterSystem/BaseCharacter.h"
#include "Campus/Core/CharacterSystem/BaseController.h"
#include "Campus/Core/CharacterSystem/Custom/VRCharacter.h"
#include "Engine/World.h"
#include "GameFramework/GameSession.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"

void ASinglePlayerGameMode::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	UWorld* World =	GetWorld();

	if(PlayerController && World)
	{
		if(CheckHMDConnection())
		{
			if(AVRCharacter* VRCharacter = World->SpawnActor<AVRCharacter>(VRCharacterClass, GetFirstPlayerStartTransform()))
			{
				PlayerController->Possess(VRCharacter);
				PlayerController->bAutoManageActiveCameraTarget = false;
				UE_LOG(LogSinglePlayerGameMode, Warning, TEXT("VR Mode"));

			}
		}
		else
		{
			if(ABaseCharacter* PCCharacter = World->SpawnActor<ABaseCharacter>(PCCharacterClass,GetFirstPlayerStartTransform()))
			{
				PlayerController->Possess(PCCharacter);
				if(ABaseController* BaseController = Cast<ABaseController>(PlayerController))
				{
					BaseController->SetupPCInputContext();
				}
				UE_LOG(LogSinglePlayerGameMode, Warning, TEXT("PC Mode"));
			}
		}
	}
}

bool ASinglePlayerGameMode::CheckHMDConnection()
{
	IHeadMountedDisplay *pHmd = nullptr;
	TSharedPtr<IStereoRendering, ESPMode::ThreadSafe> pStereo = nullptr;

	if(GEngine)
	{
		if(GEngine->XRSystem)
		{
			pHmd = GEngine->XRSystem->GetHMDDevice();
			pStereo = GEngine->XRSystem->GetStereoRenderingDevice();
		}
	}

	if(pHmd && pStereo)
	{
		if(pHmd->IsHMDConnected() && pHmd->IsHMDEnabled() && pStereo->IsStereoEnabled())
		{
			pHmd->EnableHMD();
			return true;
		}
	}

	return false;
}

FTransform ASinglePlayerGameMode::GetFirstPlayerStartTransform()	const
{
	if(UWorld* World = GetWorld())
	{
		if(AActor* PlayerStart = UGameplayStatics::GetActorOfClass(World, APlayerStart::StaticClass()))
		{
			return PlayerStart->GetActorTransform();
		}
	}
	return FTransform();
}
