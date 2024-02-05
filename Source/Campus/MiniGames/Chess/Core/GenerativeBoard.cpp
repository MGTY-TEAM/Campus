// Fill out your copyright notice in the Description page of Project Settings.


#include "GenerativeBoard.h"

#include "BasePiece.h"
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
	UHTTPAiMyLogicRequestsLib::CreateGameWithAI([this](const FString& GameID)
	{
		UE_LOG(LogTemp, Warning, TEXT("Game_ID: %s"), *GameID);
		CurrentGameID = GameID;
	}, true);
}

void AGenerativeBoard::OnCellClicked(int X, int Y)
{
	FString UCICommand;


	UCICommand += HorisontalUCI[Y];

	UCICommand += FString::FromInt(X + 1);
	UE_LOG(LogTemp, Error, TEXT("%s"), *UCICommand);

	if (SelectedCells.Key.IsEmpty())
	{
		SelectedCells.Key = UCICommand;
	}
	else if (SelectedCells.Value.IsEmpty())
	{
		SelectedCells.Value = UCICommand;
		UE_LOG(LogTemp, Error, TEXT("%s%s"), *SelectedCells.Key, *SelectedCells.Value)
		TryToPlayerMove(SelectedCells.Key + SelectedCells.Value);
		SelectedCells = TPair<FString, FString>();
	}
}

void AGenerativeBoard::TryToPlayerMove(const FString& UCI)
{
	UHTTPAiMyLogicRequestsLib::MakeMove([this,UCI](bool bMoveValid, const FString& AiMove, const FString& GameStatus)
	{
		if (bMoveValid)
		{
			MakeMove(UCI);
			MakeMove(AiMove);
		}
	}, CurrentGameID, UCI);
}

void AGenerativeBoard::OnBoardUpdated(const FString& Fen)
{
	UE_LOG(LogTemp, Warning, TEXT("Fen:%s"), *Fen);
}

void AGenerativeBoard::MakeMove(const FString& UCI)
{
	FString FirstKey = "";
	FirstKey += UCI[0];
	int32 IFirst = RverseHorisontalUCI[FirstKey];
	int32 JFirst = FCString::Atoi(*UCI.Mid(1, 1)) - 1;

	FString SecondKey = "";
	SecondKey += UCI[2];
	int32 ISecond = RverseHorisontalUCI[SecondKey];
	int32 JSecond = FCString::Atoi(*UCI.Mid(3, 1)) - 1;

	ABoardCell* FirstCell = Board[JFirst][IFirst];
	ABoardCell* SecondCell = Board[JSecond][ISecond];
	if (FirstCell && SecondCell)
	{
		if (FirstCell->Piece)
		{
			FirstCell->Piece->SetActorLocation(FVector(SecondCell->GetActorLocation().X,
			                                           SecondCell->GetActorLocation().Y,
			                                           FirstCell->Piece->GetActorLocation().Z));
			if (SecondCell->Piece)
			{
				SecondCell->Piece->Destroy();
				SecondCell->Piece = FirstCell->Piece;
				FirstCell->Piece = nullptr;
			}
			else
			{
				SecondCell->Piece = FirstCell->Piece;
				FirstCell->Piece = nullptr;
			}
		}
	}
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
		Board.Add(TArray<ABoardCell*>());
		for (int j = 0; j < 8; j++)
		{
			FVector CellPos = FVector(StartupPos.X - j * Padding, StartupPos.Y + i * Padding, StartupPos.Z);

			ABoardCell* BoardCell = GetWorld()->SpawnActor<ABoardCell>(BoardCellClass, CellPos, FRotator());
			Board[i].Add(BoardCell);
			switch (StartupPattern[i][j])
			{
			case 0:
				BoardCell->SetUpCell(TPair<int, int>(i, j), nullptr,
									 i >= 6 ? BlackPieceMaterial : WhitePieceMaterial);
				break;
			case 1:
				BoardCell->SetUpCell(TPair<int, int>(i, j),
				                     GetWorld()->SpawnActor<ABasePiece>(PawnClass, BoardCell->GetActorTransform()),
				                     i >= 6 ? BlackPieceMaterial : WhitePieceMaterial);
				break;
			case 2:
				BoardCell->SetUpCell(TPair<int, int>(i, j),
				GetWorld()->SpawnActor<ABasePiece>(KnightClass, BoardCell->GetActorTransform()),
				i >= 6 ? BlackPieceMaterial : WhitePieceMaterial);
				break;
			case 3:
				BoardCell->SetUpCell(TPair<int, int>(i, j),
				GetWorld()->SpawnActor<ABasePiece>(BishopClass, BoardCell->GetActorTransform()),
				i >= 6 ? BlackPieceMaterial : WhitePieceMaterial);
				break;
			case 4:
				BoardCell->SetUpCell(TPair<int, int>(i, j),
				GetWorld()->SpawnActor<ABasePiece>(RookClass, BoardCell->GetActorTransform()),
				i >= 6 ? BlackPieceMaterial : WhitePieceMaterial);
				break;
			case 5:
				BoardCell->SetUpCell(TPair<int, int>(i, j),
				GetWorld()->SpawnActor<ABasePiece>(QuinClass, BoardCell->GetActorTransform()),
				i >= 6 ? BlackPieceMaterial : WhitePieceMaterial);
				break;
			case 6:
				BoardCell->SetUpCell(TPair<int, int>(i, j),
				GetWorld()->SpawnActor<ABasePiece>(KingClass, BoardCell->GetActorTransform()),
				i >= 6 ? BlackPieceMaterial : WhitePieceMaterial);
				break;
			default: break;
			}
			if ((i + j) % 2 == 0)
			{
				BoardCell->SetUpColor(BlackCellMaterial, false);
			}
			else
			{
				BoardCell->SetUpColor(WhiteCellMaterial, true);
			}
			BoardCell->OnCellClicked.AddUObject(this, &AGenerativeBoard::OnCellClicked);
		}
	}
}
