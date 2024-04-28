// Fill out your copyright notice in the Description page of Project Settings.

#include "Campus/MiniGames/SolarSystem/SolarSystemGame.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Campus/MiniGames/SolarSystem/SpaceObject.h"
#include "Campus/MiniGames/SolarSystem/SpaceObjectSpot.h"

DEFINE_LOG_CATEGORY_STATIC(LogSolarSystemGame, All, All);

ASolarSystemGame::ASolarSystemGame()
{
	PrimaryActorTick.bCanEverTick = true;
	TheSun = nullptr;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	SetRootComponent(StaticMeshComponent);
	
	NiagaraComponentStars = CreateDefaultSubobject<UNiagaraComponent>("Stars");
	NiagaraComponentStars->SetupAttachment(GetRootComponent());

	NiagaraComponentCosmicDust = CreateDefaultSubobject<UNiagaraComponent>("CosmicDust");
	NiagaraComponentCosmicDust->SetupAttachment(GetRootComponent());
}

void ASolarSystemGame::BeginPlay()
{
	Super::BeginPlay();

	if (SpaceObjectSpots.Num() != 0)
	{
		for (ASpaceObjectSpot* PickupSocket : SpaceObjectSpots)
		{
			if (PickupSocket)
			{
				PickupSocket->OnChangeState.AddDynamic(this, &ASolarSystemGame::OnChangeState);
				ExecuteMiniGameCompleted.AddDynamic(PickupSocket, &ASpaceObjectSpot::OnGameCompleted);
			}
		}
	}

	if (NiagaraComponentStars && NiagaraComponentCosmicDust)
	{
		NiagaraComponentStars->SetAsset(NiagaraSystemStars);
		NiagaraComponentStars->Deactivate();

		NiagaraComponentCosmicDust->SetAsset(NiagaraSystemCosmicDust);
		NiagaraComponentCosmicDust->Deactivate();
	}

	if (LampsToOff.Num() != 0)
	{
		ExecuteMiniGameCompleted.AddDynamic(this, &ASolarSystemGame::OnGameCompleted);
	}
}

void ASolarSystemGame::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASolarSystemGame::OnChangeState()
{
	bool ShouldStartSystem = true;
	for (const ASpaceObjectSpot* PickupSocket : SpaceObjectSpots)
	{
		if (PickupSocket)
		{
			if (!PickupSocket->GetStatus())
			{
				ShouldStartSystem = false;
				break;
			}
		}
	}
	
	if (ShouldStartSystem)
	{
		StartSystem();
	}
}

void ASolarSystemGame::StartSystem()
{
	for (const ASpaceObjectSpot* PickupSocket : SpaceObjectSpots)
	{
		if (PickupSocket)
		{
			if (ASpaceObject* SpaceObject = PickupSocket->GetCorrectPlanet())
			{
				SpaceObject->SetOldCenterLocation(SpaceObject->GetCenterOfRotation()->GetActorLocation());
				SpaceObject->SetCanRotateInTrue();
			}
		}
	}

	ExecuteMiniGameCompleted.Broadcast();
	UE_LOG(LogSolarSystemGame, Display, TEXT("Solar System Game Was Complited"));
	
	if (GetWorld())
	{
		if (NiagaraComponentStars && NiagaraComponentStars->GetAsset())
		{
			NiagaraComponentStars->ActivateSystem();
		}

		if (NiagaraComponentCosmicDust && NiagaraComponentCosmicDust->GetAsset())
		{
			NiagaraComponentCosmicDust->ActivateSystem();
		}
	}
}

void ASolarSystemGame::SpawnVFX(UNiagaraSystem* VFXToSpawn, const FVector& Location, const FVector& SpawnOffset) const
{
	if (!VFXToSpawn || !GetWorld()) return;

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), VFXToSpawn, Location + SpawnOffset);
}

void ASolarSystemGame::OnGameCompleted_Implementation()
{
	UE_LOG(LogSolarSystemGame, Warning, TEXT("Function OnGameCompleted isn't override in Blueprints!"));
}

