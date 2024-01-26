// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Campus/MiniGames/Chess/Core/BasePiece.h"
#include "ChPawn.generated.h"

UCLASS()
class CAMPUS_API AChPawn : public ABasePiece
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AChPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
