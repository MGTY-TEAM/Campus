// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Campus/MiniGames/Chess/Core/BasePiece.h"
#include "ChRook.generated.h"

UCLASS()
class CAMPUS_API AChRook : public ABasePiece
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AChRook();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual TMap<int, int> GetPossibleMoves() override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
