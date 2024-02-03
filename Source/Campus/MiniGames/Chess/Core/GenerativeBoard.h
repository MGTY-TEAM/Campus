// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BoardCell.h"
#include "Templates/Tuple.h"
#include "GameFramework/Actor.h"
#include "GenerativeBoard.generated.h"


UCLASS()
class CAMPUS_API AGenerativeBoard : public AActor
{
	GENERATED_BODY()

	TArray<TArray<ABoardCell*>> Board;
public:
	// Sets default values for this actor's properties
	AGenerativeBoard();
	
	UPROPERTY(EditDefaultsOnly, Category="Classes")
	TSubclassOf<ABoardCell> BoardCellClass;

	UPROPERTY(EditAnywhere)
	float Padding = 100.f;

	UPROPERTY(EditAnywhere, Category="Cell Material")
	UMaterialInstance* BlackMaterial;
	UPROPERTY(EditAnywhere, Category="Cell Material")
	UMaterialInstance* WhiteMaterial;
	UFUNCTION()
	void OnCellClicked(int X, int Y);
	UFUNCTION()
	void OnBoardUpdated(const FString& Fen);
	FString CurrentGameID;
	
	TPair<FString, FString> SelectedCells;

	UPROPERTY(EditDefaultsOnly, Category="PiecesClasses")
	TSubclassOf<ABasePiece> PawnClass;
	UPROPERTY(EditDefaultsOnly, Category="PiecesClasses")
	TSubclassOf<ABasePiece> KnightClass;
	UPROPERTY(EditDefaultsOnly, Category="PiecesClasses")
	TSubclassOf<ABasePiece> BishopClass;
	UPROPERTY(EditDefaultsOnly, Category="PiecesClasses")
	TSubclassOf<ABasePiece> RookClass;
	UPROPERTY(EditDefaultsOnly, Category="PiecesClasses")
	TSubclassOf<ABasePiece> QuinClass;
	UPROPERTY(EditDefaultsOnly, Category="PiecesClasses")
	TSubclassOf<ABasePiece> KingClass;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void GenerateBoard();
};
