// Fill out your copyright notice in the Description page of Project Settings.

#include "GenerativeBoard.h"

#include "BasePiece.h"
#include "BoardCell.h"
#include "Campus/Libraries/MiniGames/Chess/ChessAuxiliaryLib.h"
#include "Campus/Libraries/Requests/Services/HTTPAiMyLogicRequestsLib.h"

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

	OnPlayerMoveCompleted.AddLambda([this]()
	{
		bPlayerTurn = false;
		UHTTPAiMyLogicRequestsLib::MakeAiMove(
			[this](const FString& AIMove, const FString& AICastle, const FString& GameStatus, const FString& CurrentFen)
			{
				ExecuteAIMove(AIMove, AICastle, CurrentFen);
			}, CurrentGameID);
	});

	OnAIMoveCompleted.AddLambda([this]()
	{
		bPlayerTurn = true;
	});
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
		if (bPlayerTurn)
		{
			TryToPlayerMove(SelectedCells.Key + SelectedCells.Value);
		}
		SelectedCells = TPair<FString, FString>();
	}
}

void AGenerativeBoard::TryToPlayerMove(const FString& UCI)
{
	UHTTPAiMyLogicRequestsLib::MakeMove(
		[this,UCI](bool bMoveValid, const FString& PlayerCastle, const FString& GameStatus, const FString& CurrentFen)
		{
			if (bMoveValid)
			{
				ExecutePlayerMove(UCI, PlayerCastle, CurrentFen);
				UE_LOG(LogTemp, Warning, TEXT("Ход запущен"));
			}
		}, CurrentGameID, UCI);
}

void AGenerativeBoard::TryToAIMove(const FString& UCI)
{
}

void AGenerativeBoard::OnBoardUpdated(const FString& Fen)
{
	UE_LOG(LogTemp, Warning, TEXT("Fen:%s"), *Fen);
}


void AGenerativeBoard::ExecutePlayerMove(const FString& UCI, const FString& CastleStatus, const FString& NewFen)
{
	/*FString FirstKey = "";
	FirstKey += UCI[0];
	int32 IFirst = RverseHorisontalUCI[FirstKey];
	int32 JFirst = FCString::Atoi(*UCI.Mid(1, 1)) - 1;

	FString SecondKey = "";
	SecondKey += UCI[2];
	int32 ISecond = RverseHorisontalUCI[SecondKey];
	int32 JSecond = FCString::Atoi(*UCI.Mid(3, 1)) - 1;

	ABoardCell* FirstCell = Board[JFirst][IFirst];
	ABoardCell* SecondCell = Board[JSecond][ISecond];


	TArray<FString> FenMatrix = UChessAuxiliaryLib::FenToFenMatrix(NewFen);


	for (int i = 0, k = FenMatrix.Num() - 1; i < FenMatrix.Num() && k >= 0; i++, k--)
	{
		for (int j = 0, d = FenMatrix.Num() - 1; j < FenMatrix.Num() && d >= 0; j++, d--)
		{
			ABoardCell* BoardCell = Board[k][d];
			if (FenMatrix[i][j] == '0')
			{
				if (BoardCell->Piece)
				{
					BoardCell->Piece->Destroy();
				}
			}
			else
			{
				if (BoardCell->Piece) BoardCell->Piece->Destroy();
				
				const TCHAR Char = FenMatrix[i][j];
				const bool bWhite = FChar::IsUpper(FenMatrix[i][j]);
				
				UClass* Class = bWhite ? UChessAuxiliaryLib::FenCharToWhitePieceClass[Char] : UChessAuxiliaryLib::FenCharToBlackPieceClass[Char];
				
				ABasePiece* BasePiece = GetWorld()->SpawnActor<ABasePiece>(
					Class, BoardCell->GetActorTransform());
				if (BasePiece)
				{
					BasePiece->SetUpColor(bWhite,WhitePieceMaterial, BlackPieceMaterial);
					BoardCell->Piece = BasePiece;
				}
			}
		}
	}
	OnPlayerMoveCompleted.Broadcast();*/
	/*if (FirstCell && SecondCell)
	{
		if (FirstCell->Piece)
		{
			ABasePiece* FirstPiece = FirstCell->Piece;

			CurrentPieceAnimationPoint = 0.0f;
			GetWorld()->GetTimerManager().SetTimer(PieceAnimationTimerHandle,
			                                       [this,FirstPiece,SecondCell,FirstCell]()
			                                       {
				                                       if (CurrentPieceAnimationPoint >= 1.0f)
				                                       {
					                                       UE_LOG(LogTemp, Error, TEXT("Таймер очистился!"));
					                                       GetWorld()->GetTimerManager().ClearTimer(
						                                       PieceAnimationTimerHandle);
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
					                                       OnPlayerMoveCompleted.Broadcast();
				                                       }
				                                       else
				                                       {
					                                       CurrentPieceAnimationPoint += PieceAnimationFrequency;
					                                       float NewLocationX = FMath::Lerp(
						                                       FirstPiece->GetActorLocation().X,
						                                       SecondCell->GetActorLocation().X,
						                                       CurrentPieceAnimationPoint);
					                                       float NewLocationY = FMath::Lerp(
						                                       FirstPiece->GetActorLocation().Y,
						                                       SecondCell->GetActorLocation().Y,
						                                       CurrentPieceAnimationPoint);
					                                       FirstPiece->SetActorLocation(
						                                       FVector(NewLocationX, NewLocationY,
						                                               FirstPiece->GetActorLocation().Z));
					                                       UE_LOG(LogTemp, Warning, TEXT("Таймер сработал!"));
				                                       }
			                                       }, PieceAnimationFrequency, true);
		}
	}*/
}

void AGenerativeBoard::ExecuteAIMove(const FString& UCI, const FString& CastleStatus, const FString& NewFen)
{
	/*FString FirstKey = "";
	FirstKey += UCI[0];
	int32 IFirst = RverseHorisontalUCI[FirstKey];
	int32 JFirst = FCString::Atoi(*UCI.Mid(1, 1)) - 1;

	FString SecondKey = "";
	SecondKey += UCI[2];
	int32 ISecond = RverseHorisontalUCI[SecondKey];
	int32 JSecond = FCString::Atoi(*UCI.Mid(3, 1)) - 1;

	ABoardCell* FirstCell = Board[JFirst][IFirst];
	ABoardCell* SecondCell = Board[JSecond][ISecond];


	TArray<FString> FenMatrix = UChessAuxiliaryLib::FenToFenMatrix(NewFen);


	for (int i = 0, k = FenMatrix.Num() - 1; i < FenMatrix.Num() && k >= 0; i++, k--)
	{
		for (int j = 0, d = FenMatrix.Num() - 1; j < FenMatrix.Num() && d >= 0; j++, d--)
		{
			ABoardCell* BoardCell = Board[k][d];
			if (FenMatrix[i][j] == '0')
			{
				if (BoardCell->Piece)
				{
					BoardCell->Piece->Destroy();
				}
			}
			else
			{
				if (BoardCell->Piece) BoardCell->Piece->Destroy();
				
				const TCHAR Char = FenMatrix[i][j];
				const bool bWhite = FChar::IsUpper(FenMatrix[i][j]);
				
				UClass* Class = bWhite ? UChessAuxiliaryLib::FenCharToWhitePieceClass[Char] : UChessAuxiliaryLib::FenCharToBlackPieceClass[Char];
				
				ABasePiece* BasePiece = GetWorld()->SpawnActor<ABasePiece>(Class, BoardCell->GetActorTransform());
				if (BasePiece)
				{
					BasePiece->SetUpColor(bWhite,WhitePieceMaterial, BlackPieceMaterial);
					BoardCell->Piece = BasePiece;
				}
			}
		}
	}
	OnAIMoveCompleted.Broadcast();*/
	/*if (FirstCell && SecondCell)
	{
		if (FirstCell->Piece)
		{
			ABasePiece* FirstPiece = FirstCell->Piece;

			CurrentPieceAnimationPoint = 0.0f;
			GetWorld()->GetTimerManager().SetTimer(PieceAnimationTimerHandle,
			                                       [this,FirstPiece,SecondCell,FirstCell]()
			                                       {
				                                       if (CurrentPieceAnimationPoint >= 1.0f)
				                                       {
					                                       UE_LOG(LogTemp, Error, TEXT("Таймер очистился!"));
					                                       GetWorld()->GetTimerManager().ClearTimer(
						                                       PieceAnimationTimerHandle);
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
					                                       OnAIMoveCompleted.Broadcast();
				                                       }
				                                       else
				                                       {
					                                       CurrentPieceAnimationPoint += PieceAnimationFrequency;
					                                       float NewLocationX = FMath::Lerp(
						                                       FirstPiece->GetActorLocation().X,
						                                       SecondCell->GetActorLocation().X,
						                                       CurrentPieceAnimationPoint);
					                                       float NewLocationY = FMath::Lerp(
						                                       FirstPiece->GetActorLocation().Y,
						                                       SecondCell->GetActorLocation().Y,
						                                       CurrentPieceAnimationPoint);
					                                       FirstPiece->SetActorLocation(
						                                       FVector(NewLocationX, NewLocationY,
						                                               FirstPiece->GetActorLocation().Z));
					                                       UE_LOG(LogTemp, Warning, TEXT("Таймер сработал!"));
				                                       }
			                                       }, PieceAnimationFrequency, true);
		}
	}*/
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
				                     GetWorld()->SpawnActor<ABasePiece>(UChessAuxiliaryLib::GetPawnClass(),
				                                                        BoardCell->GetActorTransform()),
				                     i >= 6 ? BlackPieceMaterial : WhitePieceMaterial);
				break;
			case 2:
				BoardCell->SetUpCell(TPair<int, int>(i, j),
				                     GetWorld()->SpawnActor<
					                     ABasePiece>(UChessAuxiliaryLib::GetKnightClass(),
					                                 BoardCell->GetActorTransform()),
				                     i >= 6 ? BlackPieceMaterial : WhitePieceMaterial);
				break;
			case 3:
				BoardCell->SetUpCell(TPair<int, int>(i, j),
				                     GetWorld()->SpawnActor<
					                     ABasePiece>(UChessAuxiliaryLib::GetBishopClass(),
					                                 BoardCell->GetActorTransform()),
				                     i >= 6 ? BlackPieceMaterial : WhitePieceMaterial);
				break;
			case 4:
				BoardCell->SetUpCell(TPair<int, int>(i, j),
				                     GetWorld()->SpawnActor<ABasePiece>(UChessAuxiliaryLib::GetRookClass(),
				                                                        BoardCell->GetActorTransform()),
				                     i >= 6 ? BlackPieceMaterial : WhitePieceMaterial);
				break;
			case 5:
				BoardCell->SetUpCell(TPair<int, int>(i, j),
				                     GetWorld()->SpawnActor<ABasePiece>(UChessAuxiliaryLib::GetQuinClass(),
				                                                        BoardCell->GetActorTransform()),
				                     i >= 6 ? BlackPieceMaterial : WhitePieceMaterial);
				break;
			case 6:
				BoardCell->SetUpCell(TPair<int, int>(i, j),
				                     GetWorld()->SpawnActor<ABasePiece>(UChessAuxiliaryLib::GetKingClass(),
				                                                        BoardCell->GetActorTransform()),
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
