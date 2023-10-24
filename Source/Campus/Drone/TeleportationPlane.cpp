// Fill out your copyright notice in the Description page of Project Settings.


#include "TeleportationPlane.h"

#include "Components/StaticMeshComponent.h"

// Sets default values
ATeleportationPlane::ATeleportationPlane()
{
	PrimaryActorTick.bCanEverTick = true;
	
	RobotPlane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RobotPlane"));
	PlayerPlane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerPlane"));
}

// Called when the game starts or when spawned
void ATeleportationPlane::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATeleportationPlane::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

