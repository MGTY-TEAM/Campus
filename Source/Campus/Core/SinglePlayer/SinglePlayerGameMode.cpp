// Fill out your copyright notice in the Description page of Project Settings.


#include "SinglePlayerGameMode.h"

#include "Engine/World.h"


void ASinglePlayerGameMode::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	PlayerController->SetInputMode(FInputModeGameOnly());
	PlayerController->bShowMouseCursor = false;
}
