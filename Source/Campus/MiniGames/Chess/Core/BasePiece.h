// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePiece.generated.h"



UCLASS()
class CAMPUS_API ABasePiece : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* StaticMeshComponent;
	
public:
	ABasePiece();
	
	void MakeMove();
	
	virtual TMap<int, int> GetPossibleMoves();
	
protected:
	virtual void BeginPlay() override;
	
	
};
