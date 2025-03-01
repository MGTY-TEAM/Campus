﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePiece.generated.h"



UCLASS()
class CAMPUS_API ABasePiece : public AActor
{
	GENERATED_BODY()


	
public:

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* StaticMeshComponent;
	ABasePiece();
	
	void MakeMove();
	
	virtual TMap<int, int> GetPossibleMoves();
	virtual void SetUpColor(bool bisWhite, UMaterialInstance* White, UMaterialInstance* Black);
	bool bWhite;
protected:
	virtual void BeginPlay() override;
	
	
};
