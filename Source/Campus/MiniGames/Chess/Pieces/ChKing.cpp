// Fill out your copyright notice in the Description page of Project Settings.


#include "ChKing.h"


// Sets default values
AChKing::AChKing()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AChKing::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AChKing::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

