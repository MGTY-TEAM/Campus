// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoardCell.generated.h"

class ABasePiece;

UCLASS()
class CAMPUS_API ABoardCell : public AActor
{
	GENERATED_BODY()
	ABasePiece* Piece;

	UPROPERTY(EditDefaultsOnly, Category="Mesh")
	UStaticMeshComponent* StaticMeshComponent;
	UPROPERTY(EditDefaultsOnly)
	USceneComponent* SceneComponent;
public:
	// Sets default values for this actor's properties
	ABoardCell();

	virtual void SetMaterial(UMaterialInstance* Material);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	virtual void PlacePiece(ABasePiece* NewPiece);
};
