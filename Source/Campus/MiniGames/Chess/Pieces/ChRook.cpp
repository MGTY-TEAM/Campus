// Fill out your copyright notice in the Description page of Project Settings.


#include "ChRook.h"


AChRook::AChRook()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AChRook::BeginPlay()
{
	Super::BeginPlay();
	
}

TMap<int, int> AChRook::GetPossibleMoves()
{
	return Super::GetPossibleMoves();
}

// Called every frame
void AChRook::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

