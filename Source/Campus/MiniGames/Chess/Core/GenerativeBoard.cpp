// Fill out your copyright notice in the Description page of Project Settings.


#include "GenerativeBoard.h"

#include "BoardCell.h"
#include "Campus/Libraries/Requests/Services/HTTPAiMyLogicRequestsLib.h"
#include "GameFramework/FloatingPawnMovement.h"


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

void AGenerativeBoard::OnCellClicked(int X, int Y)
{
	FString UCICommand;
	switch (Y)
	{
	case 0:
		UCICommand += "a";
		break;
	case 1:
		UCICommand += "b";
		break;
	case 2:
		UCICommand += "c";
		break;
	case 3:
		UCICommand += "d";
		break;
	case 4:
		UCICommand += "e";
		break;
	case 5:
		UCICommand += "f";
		break;
	case 6:
		UCICommand += "g";
		break;
	case 7:
		UCICommand += "h";
		break;
	default:
		return;
	}
	UCICommand += FString::FromInt(X+1);
	UE_LOG(LogTemp, Error, TEXT("%s"), *UCICommand);

	if (SelectedCells.Key.IsEmpty())
	{
		SelectedCells.Key = UCICommand;
	}
	else if (SelectedCells.Value.IsEmpty())
	{
		SelectedCells.Value = UCICommand;
		UHTTPAiMyLogicRequestsLib::MakeMove(CurrentGameID, SelectedCells.Key + SelectedCells.Value, false);
		SelectedCells = TPair<FString, FString>();
	}
}

void AGenerativeBoard::OnBoardUpdated(const FString& Fen)
{
	UE_LOG(LogTemp, Warning, TEXT("Fen:%s"), *Fen);
}

void AGenerativeBoard::GenerateBoard()
{
	TArray<TArray<int>> StartupPattern =
	{
		{4, 2, 3, 5, 6, 3, 2, 4},
		{1, 1, 1, 1, 1, 1, 1, 1},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{1, 1, 1, 1, 1, 1, 1, 1},
		{4, 2, 3, 5, 6, 3, 2, 4}
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
				BoardCell->SetUpCell(BlackMaterial, TPair<int, int>(i, j));
			}
			else
			{
				BoardCell->SetUpCell(WhiteMaterial, TPair<int, int>(i, j));
			}
			BoardCell->OnCellClicked.AddUObject(this, &AGenerativeBoard::OnCellClicked);
		}
	}
}
