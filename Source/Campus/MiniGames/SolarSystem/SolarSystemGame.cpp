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
	
	// SceneComponentStars = CreateDefaultSubobject<USceneComponent>("SceneStars");
	// SceneComponentStars->SetupAttachment(GetRootComponent());

	// SceneComponentCosmicDust = CreateDefaultSubobject<USceneComponent>("SceneCosmicDust");
	// SceneComponentCosmicDust->SetupAttachment(GetRootComponent());
	
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

	if (GetWorld())
	{
		/* if (NiagaraSystemStars && SceneComponentStars)
		{
			SpawnVFX(NiagaraSystemStars, SceneComponentStars->GetComponentLocation(),  FVector(0.f));
		}
		if (NiagaraSystemCosmicDust && SceneComponentCosmicDust)
		{
			SpawnVFX(NiagaraSystemCosmicDust, SceneComponentCosmicDust->GetComponentLocation(),  FVector(0.f));
		} */
		
		if (NiagaraComponentStars && NiagaraComponentStars->GetAsset())
		{
			// NiagaraComponentStars->SetAsset(NiagaraSystemStars);
			NiagaraComponentStars->ActivateSystem();
			// SpawnVFX(NiagaraComponentStars->GetAsset(), NiagaraComponentStars->GetComponentLocation(), FVector(0.f));
		}

		if (NiagaraComponentCosmicDust && NiagaraComponentCosmicDust->GetAsset())
		{
			// NiagaraComponentCosmicDust->SetAsset(NiagaraSystemCosmicDust);
			NiagaraComponentCosmicDust->ActivateSystem();
			// SpawnVFX(NiagaraComponentCosmicDust->GetAsset(), NiagaraComponentCosmicDust->GetComponentLocation(), FVector(0.f));
		}
	}
	
	ExecuteMiniGameCompleted.Broadcast();
	UE_LOG(LogSolarSystemGame, Display, TEXT("Solar System Game Was Complited"));
}

void ASolarSystemGame::SpawnVFX(UNiagaraSystem* VFXToSpawn, const FVector& Location, const FVector& SpawnOffset) const
{
	if (!VFXToSpawn || !GetWorld()) return;

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), VFXToSpawn, Location + SpawnOffset);
}

