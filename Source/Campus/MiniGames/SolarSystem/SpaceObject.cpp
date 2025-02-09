// Fill out your copyright notice in the Description page of Project Settings.


#include "Campus/MiniGames/SolarSystem/SpaceObject.h"
#include "NiagaraComponent.h"
#include "Components/StaticMeshComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogSpaceObject, All, All);

ASpaceObject::ASpaceObject()
{
	PrimaryActorTick.bCanEverTick = true;
	CenterOfRotation = nullptr;

	NiagaraComponentExplosion = CreateDefaultSubobject<UNiagaraComponent>("NiagaraComponentExplosion");
	NiagaraComponentExplosion->SetupAttachment(StaticMeshComponent);
}

void ASpaceObject::BeginPlay()
{
	Super::BeginPlay();

	BeginPosition = GetActorLocation();
	if (CenterOfRotation)
	{
		OldCenterLocation = CenterOfRotation->GetActorLocation();
	}

	if (NiagaraComponentExplosion)
	{
		NiagaraComponentExplosion->SetAsset(NiagaraSystemExplosion);
		NiagaraComponentExplosion->Deactivate();
	}
}

void ASpaceObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (CenterOfRotation && CanRotate)
	{
		OrthogonalAxis();

		const FVector VectorBetweenSelfAndOld = GetActorLocation() - OldCenterLocation;
		const FVector RotatedVector = VectorBetweenSelfAndOld.RotateAngleAxis(DeltaTime * Speed, Axis);
		SetActorLocation(CenterOfRotation->GetActorLocation() + RotatedVector);
		OldCenterLocation = CenterOfRotation->GetActorLocation();
	}
}

void ASpaceObject::StartActive()
{
	SetCanRotateInTrue();
	SetCanPickup(false);
}

void ASpaceObject::EndActive()
{
	SetCanRotateInFalse();

	if (GetWorld())
	{
		GetWorldTimerManager().SetTimer(ExplosionTimerHandle, this, &ASpaceObject::OnActivateSystem, FMath::RandRange(0.5f, 3.5f), false);
	}
	// OnActivateSystem();
}

void ASpaceObject::SetEnabled(bool bEnabled)
{
	M_IsEnabled = bEnabled;
	if (bEnabled)
	{
		SetActorHiddenInGame(false);
		SetActorTickEnabled(true);
	}
	else
	{
		SetActorHiddenInGame(true);
		SetActorTickEnabled(true);
	}
}

void ASpaceObject::OrthogonalAxis()
{
	Axis = FVector::CrossProduct(GetActorLocation() - OldCenterLocation, FVector::CrossProduct(Axis, GetActorLocation() - OldCenterLocation)).GetSafeNormal();
}

void ASpaceObject::OnActivateSystem()
{
	if (GetWorld() && NiagaraComponentExplosion && StaticMeshComponent && StaticMeshComponent->GetStaticMesh())
	{
		NiagaraComponentExplosion->SetVariableStaticMesh("SM_StaticMesh", this->StaticMeshComponent->GetStaticMesh());
		NiagaraComponentExplosion->ActivateSystem();
		// const FTimerDelegate MyDelegate = FTimerDelegate::CreateUObject(NiagaraComponentExplosion, &UNiagaraComponent::ActivateSystem, false);
		// GetWorldTimerManager().SetTimer(ExplosionTimerHandle, MyDelegate, FMath::RandRange(0.5f, 3.5f), false);
	}
	ReallocatePlanet();
}

void ASpaceObject::ReallocatePlanet_Implementation()
{
	SetActorLocation(GetBeginPosition());
	SetCanPickup(true);
}
