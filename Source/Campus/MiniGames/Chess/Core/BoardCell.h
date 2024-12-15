// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoardCell.generated.h"
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCellClicked, int, int);
class ABasePiece;

UCLASS()
class CAMPUS_API ABoardCell : public AActor
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, Category="Mesh")
	UStaticMeshComponent* StaticMeshComponent;
	
	TPair<int, int> CellPos;

	UFUNCTION()
	void OnClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);
public:
	UPROPERTY(EditDefaultsOnly)
	USceneComponent* SceneComponent;
	ABoardCell();
	virtual void SetUpCell(TPair<int, int> Pos, ABasePiece* = nullptr, UMaterialInstance* PieceMaterial = nullptr);
	virtual void SetUpColor(UMaterialInstance* MaterialInstance, bool bColorWhite);
	void Click();
	ABasePiece* Piece;
	FOnCellClicked OnCellClicked;

	bool bWhite; 
protected:
	virtual void BeginPlay() override;


	virtual void PlacePiece(ABasePiece* NewPiece);
};
