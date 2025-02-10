// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInteractionDrone.h"

void APlayerInteractionDrone::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerInteractionDrone::Interact()
{
	UE_LOG(LogTemp, Warning, TEXT("NewInteract"));
}

void APlayerInteractionDrone::EndInteract()
{
	UE_LOG(LogTemp, Warning, TEXT("NewEndInteract"));
}

