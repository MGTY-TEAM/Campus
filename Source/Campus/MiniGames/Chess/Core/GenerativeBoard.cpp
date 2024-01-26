// Fill out your copyright notice in the Description page of Project Settings.


#include "GenerativeBoard.h"

#include "BoardCell.h"


// Sets default values
AGenerativeBoard::AGenerativeBoard()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AGenerativeBoard::BeginPlay()
{
	Super::BeginPlay();
	GenerateBoard();
}

void AGenerativeBoard::GenerateBoard()
{
	TArray<TArray<int>> StartupPattern =
	{
		{4,2,3,5,6,3,2,4},
		{1,1,1,1,1,1,1,1},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{1,1,1,1,1,1,1,1},
		{4,2,3,5,6,3,2,4}
	};
	FVector StartupPos = GetActorLocation();
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			FVector CellPos = FVector(StartupPos.X - j * Padding, StartupPos.Y + i * Padding, StartupPos.Z);

			ABoardCell* BoardCell = GetWorld()->SpawnActor<ABoardCell>(BoardCellClass, CellPos, FRotator());
			if ((i + j) % 2 == 0)
			{
				BoardCell->SetMaterial(BlackMaterial);
			}
			else
			{
				BoardCell->SetMaterial(WhiteMaterial);
			}
		}
	}
}


