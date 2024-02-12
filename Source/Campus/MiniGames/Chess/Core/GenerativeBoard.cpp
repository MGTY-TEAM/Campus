// Fill out your copyright notice in the Description page of Project Settings.


#include "GenerativeBoard.h"

#include "BasePiece.h"
#include "BoardCell.h"
#include "Campus/Libraries/Requests/Services/HTTPAiMyLogicRequestsLib.h"
#include "Experimental/Async/AwaitableTask.h"
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

	OnPlayerMoveCompleted.AddLambda([this]()
	{
		bPlayerTurn = false;
		UHTTPAiMyLogicRequestsLib::MakeAiMove(
			[this](const FString& AIMove, const FString& AICastle, const FString& GameStatus, const FString& CurrentFen)
			{
				ExecuteAIMove(AIMove, AICastle);
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
		[this,UCI](bool bMoveValid, const FString& PlayerCastle, const FString& GameStatus)
		{
			if (bMoveValid)
			{
				ExecutePlayerMove(UCI, PlayerCastle);
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

void AGenerativeBoard::ExecuteWhiteKingCastle(bool bPlayerMove)
{
	ABasePiece* King;
	ABasePiece* Rook;

	if (Board[0][3]->Piece)
	{
		King = Board[0][3]->Piece;
	}
	else
	{
		return;
	}

	if (Board[0][0]->Piece)
	{
		Rook = Board[0][0]->Piece;
	}
	else
	{
		return;
	}

	FVector TargetKingPosition = FVector(Board[0][1]->GetActorLocation().X, Board[0][1]->GetActorLocation().Y,
	                                     King->GetActorLocation().Z);
	FVector TargetRookPosition = FVector(Board[0][2]->GetActorLocation().X, Board[0][2]->GetActorLocation().Y,
	                                     Rook->GetActorLocation().Z);

	GetWorld()->GetTimerManager().SetTimer(PieceAnimationTimerHandle,
	                                       [this, King, Rook, TargetKingPosition, TargetRookPosition]()
	                                       {
		                                       if (CurrentPieceAnimationPoint >= 1.0f)
		                                       {
			                                       GetWorld()->GetTimerManager().ClearTimer(PieceAnimationTimerHandle);
		                                       }
		                                       else
		                                       {
			                                       CurrentPieceAnimationPoint += PieceAnimationFrequency;
			                                       King->SetActorLocation(FVector(
				                                       FMath::Lerp(GetActorLocation().X, TargetKingPosition.X,
				                                                   CurrentPieceAnimationPoint),
				                                       FMath::Lerp(GetActorLocation().X, TargetKingPosition.X,
				                                                   CurrentPieceAnimationPoint), TargetKingPosition.Z));
			                                       Rook->SetActorLocation(FVector(
				                                       FMath::Lerp(GetActorLocation().X, TargetRookPosition.X,
				                                                   CurrentPieceAnimationPoint),
				                                       FMath::Lerp(GetActorLocation().X, TargetRookPosition.X,
				                                                   CurrentPieceAnimationPoint), TargetKingPosition.Z));
		                                       }
	                                       }, PieceAnimationFrequency, true);
}

void AGenerativeBoard::ExecutePlayerMove(const FString& UCI, const FString& CastleStatus)
{
	if (!CastleStatus.IsEmpty())
	{
		switch (CastleStatus)
		{
		case FString("white_king_castle"):
			ExecuteWhiteKingCastle(true);
			break;
		case FString("white_quin_castle"):
			break;
		case FString("black_king_castle"):
			break;
		case FString("black_quin_castle"):
			break;
		default:
			break;
		}
	}
	else
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
		}
	}
}

void AGenerativeBoard::ExecuteAIMove(const FString& UCI, const FString& CastleStatus)
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
				                     GetWorld()->SpawnActor<
					                     ABasePiece>(KnightClass, BoardCell->GetActorTransform()),
				                     i >= 6 ? BlackPieceMaterial : WhitePieceMaterial);
				break;
			case 3:
				BoardCell->SetUpCell(TPair<int, int>(i, j),
				                     GetWorld()->SpawnActor<
					                     ABasePiece>(BishopClass, BoardCell->GetActorTransform()),
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
