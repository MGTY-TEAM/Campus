// Fill out your copyright notice in the Description page of Project Settings.


#include "MovableBackActor.h"


// Sets default values
AMovableBackActor::AMovableBackActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AMovableBackActor::SlideToStartPosition()
{
	FTimerHandle TimerHandle;

}

// Called when the game starts or when spawned
void AMovableBackActor::BeginPlay()
{
	Super::BeginPlay();
	StartPosition = GetActorLocation();
}

// Called every frame
void AMovableBackActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

