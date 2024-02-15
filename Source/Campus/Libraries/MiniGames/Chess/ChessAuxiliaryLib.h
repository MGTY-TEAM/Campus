// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Campus/MiniGames/Chess/Core/BasePiece.h"
#include "Campus/MiniGames/Chess/Pieces/ChBishop.h"
#include "Campus/MiniGames/Chess/Pieces/ChKing.h"
#include "Campus/MiniGames/Chess/Pieces/ChKnight.h"
#include "Campus/MiniGames/Chess/Pieces/ChPawn.h"
#include "Campus/MiniGames/Chess/Pieces/ChQuin.h"
#include "Campus/MiniGames/Chess/Pieces/ChRook.h"
#include "Engine/AssetManager.h"
#include "UObject/Object.h"
#include "ChessAuxiliaryLib.generated.h"

class ABasePiece;
/**
 * 
 */
UCLASS()
class CAMPUS_API UChessAuxiliaryLib : public UObject
{
	GENERATED_BODY()
	inline const static TMap<int32, FString> HorisontalUCI =
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
	inline const static TMap<FString, int32> RverseHorisontalUCI =
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


	inline const static FString PawnClass = "/Game/BLueprints/MiniGames/Chess/BP_ChPawn.BP_ChPawn_C";
	inline const static FString RookClass = "/Game/BLueprints/MiniGames/Chess/BP_ChRook.BP_ChRook_C";
	inline const static FString KnightClass = "/Game/BLueprints/MiniGames/Chess/BP_ChKnight.BP_ChKnight_C";
	inline const static FString BishopClass = "/Game/BLueprints/MiniGames/Chess/BP_ChBishop.BP_ChBishop_C";
	inline const static FString KingClass = "/Game/BLueprints/MiniGames/Chess/BP_ChKing.BP_ChKing_C";
	inline const static FString QuinClass = "/Game/BLueprints/MiniGames/Chess/BP_ChQuin.BP_ChQuin_C";

public:
	static TTuple<int, int, int, int> FromUCIToCoord(const FString& UCI);

	static TSubclassOf<ABasePiece> GetPawnClass()
	{
		return StaticLoadClass(ABasePiece::StaticClass(), nullptr, *PawnClass);
	}

	static TSubclassOf<ABasePiece> GetRookClass()
	{
		return StaticLoadClass(ABasePiece::StaticClass(), nullptr, *RookClass);
	}

	static TSubclassOf<ABasePiece> GetKnightClass()
	{
		return StaticLoadClass(ABasePiece::StaticClass(), nullptr, *KnightClass);
	}

	static TSubclassOf<ABasePiece> GetBishopClass()
	{
		return StaticLoadClass(ABasePiece::StaticClass(), nullptr, *BishopClass);
	}

	static TSubclassOf<ABasePiece> GetKingClass()
	{
		return StaticLoadClass(ABasePiece::StaticClass(), nullptr, *KingClass);
	}

	static TSubclassOf<ABasePiece> GetQuinClass()
	{
		return StaticLoadClass(ABasePiece::StaticClass(), nullptr, *QuinClass);
	}

	static TArray<FString> FenToFenMatrix(const FString& Fen)
	{
		TArray<FString> SubResult;
		Fen.ParseIntoArray(SubResult, TEXT(" "), true);

		TArray<FString> Result;
		if (SubResult.Num() > 0)
		{
			FString FENString = SubResult[0];
			TArray<FString> Rows;
			FENString.ParseIntoArray(Rows, TEXT("/"), true);

			for (const FString& Row : Rows)
			{
				FString NewRow = "";
				for (const TCHAR Char : Row)
				{
					if (FChar::IsDigit(Char))
					{
						const int32 ZeroCount = Char - TEXT('0');
						for (int32 i = 0; i < ZeroCount; ++i)
						{
							NewRow.AppendChar(TEXT('0'));
						}
					}
					else
					{
						NewRow.AppendChar(Char);
					}
				}
				Result.Add(NewRow);
			}
		}
		return Result;
	}

	inline static TMap<UClass*, TCHAR> BlackPieceClassToFenChar =
	{
		{AChPawn::StaticClass(), 'p'},
		{AChRook::StaticClass(), 'r'},
		{AChKnight::StaticClass(), 'n'},
		{AChBishop::StaticClass(), 'b'},
		{AChKing::StaticClass(), 'k'},
		{AChQuin::StaticClass(), 'q'}
	};

	inline static TMap<UClass*, TCHAR> WhitePieceClassToFenChar =
	{
		{AChPawn::StaticClass(), 'P'},
		{AChRook::StaticClass(), 'R'},
		{AChKnight::StaticClass(), 'N'},
		{AChBishop::StaticClass(), 'B'},
		{AChKing::StaticClass(), 'K'},
		{AChQuin::StaticClass(), 'Q'}
	};

	inline static TMap<TCHAR, UClass*> FenCharToBlackPieceClass =
	{
		{'p', AChPawn::StaticClass()},
		{'r', AChRook::StaticClass()},
		{'n', AChKnight::StaticClass()},
		{'b', AChBishop::StaticClass()},
		{'k', AChKing::StaticClass()},
		{'q', AChQuin::StaticClass()}
	};

	inline static TMap<TCHAR, UClass*> FenCharToWhitePieceClass =
	{
		{'P', AChPawn::StaticClass()},
		{'R', AChRook::StaticClass()},
		{'N', AChKnight::StaticClass()},
		{'B', AChBishop::StaticClass()},
		{'K', AChKing::StaticClass()},
		{'Q', AChQuin::StaticClass()}
	};
};
