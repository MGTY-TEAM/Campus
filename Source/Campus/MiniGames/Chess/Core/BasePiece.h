// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePiece.generated.h"

UCLASS()
class CAMPUS_API ABasePiece : public AActor
{
	GENERATED_BODY()


public:
	// Sets default values for this actor's properties
	ABasePiece();
	
	void MakeMove();

	virtual TMap<int, int> GetPossibleMoves();
protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* StaticMeshComponent;
	// Return all possible moves for piece
	
};
