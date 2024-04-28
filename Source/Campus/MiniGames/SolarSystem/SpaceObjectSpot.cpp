// Fill out your copyright notice in the Description page of Project Settings.

#include "Campus/MiniGames/SolarSystem/SpaceObjectSpot.h"
#include "Components/StaticMeshComponent.h"
#include "Campus/Inventory/InventoryActor.h"
#include "Campus/Inventory/PickupSocketComponent.h"
#include "Campus/MiniGames/SolarSystem/SpaceObject.h"

DEFINE_LOG_CATEGORY_STATIC(LogSpaceObjectSpot, All, All);

ASpaceObjectSpot::ASpaceObjectSpot()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticHandleMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("HandleMeshComponent");
	SetRootComponent(StaticHandleMeshComponent);
	
	PickupSocket = CreateDefaultSubobject<UPickupSocketComponent>("PickupSocket");
	PickupSocket->SetupAttachment(GetRootComponent());
}

void ASpaceObjectSpot::BeginPlay()
{
	Super::BeginPlay();

	if (PickupSocket)
	{
		PickupSocket->OnPickupPlaced.BindDynamic(this, &ASpaceObjectSpot::OnPickupPlaced);
		PickupSocket->OnPickupRemoved.BindDynamic(this, &ASpaceObjectSpot::OnPickupRemoved);
	}
}

void ASpaceObjectSpot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpaceObjectSpot::OnPickupPlaced(AInventoryActor* Actor)
{
	ASpaceObject* SpaceObject = Cast<ASpaceObject>(Actor);
	if (Actor)
	{
		CheckCorrectPlanet(SpaceObject);
	}
	// SpaceObject->SetOldCenterLocation(SpaceObject->GetCenterOfRotation()->GetActorLocation());
}

void ASpaceObjectSpot::OnPickupRemoved()
{
	if (CorrectPlanet)
	{
		CorrectPlanet->SetCanRotateInFalse();
	}
	
	HaveCorrectPlanet = false;
	CorrectPlanet = nullptr;
}

void ASpaceObjectSpot::CheckCorrectPlanet(ASpaceObject* SpaceObject)
{
	if (SpaceObject->GetNameOfObject() == NAME_None || NameOfSpot == NAME_None) return;
	
	if (SpaceObject->GetNameOfObject() == NameOfSpot)
	{
		HaveCorrectPlanet = true;
		CorrectPlanet = SpaceObject;
		
		OnChangeState.Broadcast();
	}
	else
	{
		HaveCorrectPlanet = false;
		CorrectPlanet = nullptr;
	}
}

void ASpaceObjectSpot::OnGameCompleted_Implementation()
{
	UE_LOG(LogSpaceObjectSpot, Warning, TEXT("Function OnGameCompleted isn't override in Blueprints!"));
}

