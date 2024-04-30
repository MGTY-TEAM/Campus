// Fill out your copyright notice in the Description page of Project Settings.


#include "Campus/MiniGames/SolarSystem/SpaceObject.h"
#include "Components/StaticMeshComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogSpaceObject, All, All);

ASpaceObject::ASpaceObject()
{
	PrimaryActorTick.bCanEverTick = true;
	CenterOfRotation = nullptr;
}

void ASpaceObject::BeginPlay()
{
	Super::BeginPlay();

	if (CenterOfRotation)
	{
		OldCenterLocation = CenterOfRotation->GetActorLocation();
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
	SetCanPickup(true);
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
