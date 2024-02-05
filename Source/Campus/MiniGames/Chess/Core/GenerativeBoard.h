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

	TMap<int32, FString> HorisontalUCI =
	{
		{0, "a"},
		{1, "b"},
		{2, "c"},
		{3, "d"},
		{4, "e"},
		{5, "f"},
		{6, "g"},
		{7, "h"},
	};
	TMap<FString, int32> RverseHorisontalUCI =
	{
		{"a", 0},
		{"b", 1},
		{"c", 2},
		{"d", 3},
		{"e", 4},
		{"f", 5},
		{"g", 6},
		{"h", 7},
	};

public:
	// Sets default values for this actor's properties
	AGenerativeBoard();

	UPROPERTY(EditDefaultsOnly, Category="Classes")
	TSubclassOf<ABoardCell> BoardCellClass;

	UPROPERTY(EditAnywhere)
	float Padding = 100.f;

	UPROPERTY(EditAnywhere, Category="Cell Material")
	UMaterialInstance* BlackCellMaterial;
	UPROPERTY(EditAnywhere, Category="Cell Material")
	UMaterialInstance* WhiteCellMaterial;

	UPROPERTY(EditAnywhere, Category="Cell Material")
	UMaterialInstance* BlackPieceMaterial;
	UPROPERTY(EditAnywhere, Category="Cell Material")
	UMaterialInstance* WhitePieceMaterial;
	UFUNCTION()
	void OnCellClicked(int X, int Y);

	void TryToPlayerMove(const FString& UCI);
	UFUNCTION()
	void OnBoardUpdated(const FString& Fen);

	void MakeMove(const FString& UCI);
	
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
