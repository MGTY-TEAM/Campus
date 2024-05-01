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

	PlacementSceneComponent = CreateDefaultSubobject<USceneComponent>("PlacementSceneComponent");
	SetRootComponent(PlacementSceneComponent);
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	StaticMeshComponent->SetupAttachment(GetRootComponent());

	StaticMeshComponentButton = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponentButton");
	StaticMeshComponentButton->SetupAttachment(StaticMeshComponent);

	StaticMeshComponentGlass = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponentGlass");
	StaticMeshComponentGlass->SetupAttachment(StaticMeshComponent);
	
	NiagaraComponentStars = CreateDefaultSubobject<UNiagaraComponent>("Stars");
	NiagaraComponentStars->SetupAttachment(GetRootComponent());

	NiagaraComponentCosmicDust = CreateDefaultSubobject<UNiagaraComponent>("CosmicDust");
	NiagaraComponentCosmicDust->SetupAttachment(GetRootComponent());
}

void ASolarSystemGame::BeginPlay()
{
	Super::BeginPlay();

	if (StaticMeshComponentGlass)
	{
		NormalRotationOfGlassCase = StaticMeshComponentGlass->GetComponentRotation();
	}
	
	if (SpaceObjectSpots.Num() != 0)
	{
		for (ASpaceObjectSpot* PickupSocket : SpaceObjectSpots)
		{
			if (PickupSocket)
			{
				PickupSocket->OnChangeState.AddDynamic(this, &ASolarSystemGame::OnChangeState);
				OnStartUniverse.AddDynamic(PickupSocket, &ASpaceObjectSpot::OnGameCompleted);
				OnDestroyUniverse.AddDynamic(PickupSocket, &ASpaceObjectSpot::OnDestroyUniverse);
			}
		}
	}

	if (NiagaraComponentStars && NiagaraComponentCosmicDust)
	{
		NiagaraComponentStars->SetAsset(NiagaraSystemStars);
		NiagaraComponentStars->Deactivate();

		NiagaraComponentCosmicDust->SetAsset(NiagaraSystemCosmicDust);
		NiagaraComponentCosmicDust->Deactivate();

		OnDestroyUniverse.AddDynamic(this, &ASolarSystemGame::DestroySystem);
	}

	if (LampsToOff.Num() != 0)
	{
		OnStartUniverse.AddDynamic(this, &ASolarSystemGame::OnStartUniverseLogic);
		OnDestroyUniverse.AddDynamic(this, &ASolarSystemGame::OnDestroyUniverseLogic);
	}
}

void ASolarSystemGame::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	InterpolateGlassCaseMesh(DeltaTime);
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
				SpaceObject->StartActive();
			}
		}
	}

	OnStartUniverse.Broadcast();
	if (!bIsGameCompleted)
	{
		ExecuteMiniGameCompleted.Broadcast();
		bIsGameCompleted = true;
		UE_LOG(LogSolarSystemGame, Display, TEXT("Solar System Game Was Complited"));
	}
	
	if (GetWorld())
	{
		if (NiagaraComponentStars && NiagaraComponentStars->GetAsset())
		{
			NiagaraComponentStars->Deactivate();
			NiagaraComponentStars->SetVariableBool("EnableMoveStars", false);
			NiagaraComponentStars->SetVariableFloat("SpawnStars", SpawnStars);
			NiagaraComponentStars->SetVariableFloat("SpawnFallingStars", SpawnFallingStars);
			NiagaraComponentStars->ActivateSystem();
		}

		if (NiagaraComponentCosmicDust && NiagaraComponentCosmicDust->GetAsset())
		{
			NiagaraComponentCosmicDust->Deactivate();
			NiagaraComponentCosmicDust->SetVariableBool("EnableDissolve", false);
			NiagaraComponentCosmicDust->SetVariableFloat("SpawnDust", 1.f);
			NiagaraComponentCosmicDust->ActivateSystem();
		}
	}

	bIsSystemWorking = true;
}

void ASolarSystemGame::DestroySystem()
{
	for (const ASpaceObjectSpot* PickupSocket : SpaceObjectSpots)
	{
		if (PickupSocket)
		{
			if (ASpaceObject* SpaceObject = PickupSocket->GetCorrectPlanet())
			{
				PickupSocket->RemovePickup();
				SpaceObject->EndActive();
			}
		}
	}

	if (GetWorld())
	{
		if (NiagaraComponentStars && NiagaraComponentStars->GetAsset())
		{
			NiagaraComponentStars->SetVariableBool("EnableMoveStars", true);
			NiagaraComponentStars->SetVariableFloat("SpawnStars", 0.f);
			NiagaraComponentStars->SetVariableFloat("SpawnFallingStars", 0.f);

			GetWorldTimerManager().SetTimer(DeactivateStarsHandle, this, &ASolarSystemGame::DeactivateStars, DeactivateRateStars, false);
		}

		if (NiagaraComponentCosmicDust && NiagaraComponentCosmicDust->GetAsset())
		{
			NiagaraComponentCosmicDust->SetVariableBool("EnableDissolve", true);
			NiagaraComponentCosmicDust->SetVariableFloat("SpawnDust", 0.f);
			GetWorldTimerManager().SetTimer(DeactivateFallingStarsHandle, this, &ASolarSystemGame::DeactivateFallingStars, DeactivateRateFallingStars, false);
		}
	}

	bIsSystemWorking = false;
}

void ASolarSystemGame::SpawnVFX(UNiagaraSystem* VFXToSpawn, const FVector& Location, const FVector& SpawnOffset) const
{
	if (!VFXToSpawn || !GetWorld()) return;

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), VFXToSpawn, Location + SpawnOffset);
}

void ASolarSystemGame::Interact(UActorComponent* InteractComponent, const FVector& InteractPoint, const FVector& InteractionNormal)
{
	if (!bIsInvisible) return;
	
	IInteractable::Interact(InteractComponent, InteractPoint, InteractionNormal);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "StartInteract");

	if (bIsGlassCaseClose)
	{
		DesiredRotationOfGlassCase = FRotator(0.f, 0.f, -110.f);
	}
	else
	{
		if (StaticMeshComponentButton)
		{
			const FVector InitialLocation = StaticMeshComponentButton->GetComponentLocation();
			StaticMeshComponentButton->SetWorldLocation(InitialLocation + FVector(1.f, 0.f, 0.0f));
		}
	}
}

void ASolarSystemGame::EndInteract_Implementation()
{
	if (!bIsInvisible) return;
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "EndInteract");

	if (bIsGlassCaseClose)
	{
		bIsGlassCaseClose = false;
	}
	else
	{
		DesiredRotationOfGlassCase = FRotator(0.f);
		bIsGlassCaseClose = true;
		
		const FVector InitialLocation = StaticMeshComponentButton->GetComponentLocation();
		StaticMeshComponentButton->SetWorldLocation(InitialLocation + FVector(-1.f, 0.f, 0.0f));
		if (bIsSystemWorking)
		{
			OnDestroyUniverse.Broadcast();
		}
	}
}

void ASolarSystemGame::DeactivateStars()
{
	NiagaraComponentStars->Deactivate();
}

void ASolarSystemGame::DeactivateFallingStars()
{
	NiagaraComponentCosmicDust->Deactivate();
}

void ASolarSystemGame::InterpolateGlassCaseMesh(float DeltaTime)
{
	if (!StaticMeshComponentGlass) return;

	const FRotator InitialRotation = StaticMeshComponentGlass->GetComponentRotation();

	if (InitialRotation != NormalRotationOfGlassCase + DesiredRotationOfGlassCase)
	{
		const FRotator NewRotation = FMath::RInterpTo(InitialRotation,NormalRotationOfGlassCase + DesiredRotationOfGlassCase, DeltaTime, 5.f);
		StaticMeshComponentGlass->SetWorldRotation(NewRotation);
	}
}

