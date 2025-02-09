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
 * Utility class providing auxiliary functions and data for Chess game.
 */
UCLASS()
class CAMPUS_API UChessAuxiliaryLib : public UObject
{
	GENERATED_BODY()

public:
	/**
	 * Convert a given UCI (Universal Chess Interface) string to coordinates.
	 * UCI format example: "a2a4".
	 *
	 * @param UCI The UCI string representing the move.
	 * @return Tuple representing the coordinates of the move.
	 *         Tuple format: (row of origin, column of origin, row of destination, column of destination).
	 *         Row and column indices are 0-based.
	 */
	static TTuple<int, int, int, int> FromUCIToCoord(const FString& UCI);

	/**
	 * Get the class of Pawn piece.
	 *
	 * @return Class of Pawn piece.
	 */
	static TSubclassOf<ABasePiece> GetPawnClass()
	{
		return StaticLoadClass(ABasePiece::StaticClass(), nullptr, *PawnClass);
	}

	/**
	 * Get the class of Rook piece.
	 *
	 * @return Class of Rook piece.
	 */
	static TSubclassOf<ABasePiece> GetRookClass()
	{
		return StaticLoadClass(ABasePiece::StaticClass(), nullptr, *RookClass);
	}

	/**
	 * Get the class of Knight piece.
	 *
	 * @return Class of Knight piece.
	 */
	static TSubclassOf<ABasePiece> GetKnightClass()
	{
		return StaticLoadClass(ABasePiece::StaticClass(), nullptr, *KnightClass);
	}

	/**
	 * Get the class of Bishop piece.
	 *
	 * @return Class of Bishop piece.
	 */
	static TSubclassOf<ABasePiece> GetBishopClass()
	{
		return StaticLoadClass(ABasePiece::StaticClass(), nullptr, *BishopClass);
	}

	/**
	 * Get the class of King piece.
	 *
	 * @return Class of King piece.
	 */
	static TSubclassOf<ABasePiece> GetKingClass()
	{
		return StaticLoadClass(ABasePiece::StaticClass(), nullptr, *KingClass);
	}

	/**
	 * Get the class of Queen piece.
	 *
	 * @return Class of Queen piece.
	 */
	static TSubclassOf<ABasePiece> GetQuinClass()
	{
		return StaticLoadClass(ABasePiece::StaticClass(), nullptr, *QuinClass);
	}

	/**
	 * Convert a given FEN (Forsyth–Edwards Notation) string to a matrix representation.
	 * FEN format example: "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR".
	 *
	 * @param Fen The FEN string representing the current board state.
	 * @return Array of strings representing the matrix representation of the board.
	 */
	static TArray<FString> FenToFenMatrix(const FString& Fen);

	// Mapping of black piece classes to their FEN representation characters.
	inline static TMap<UClass*, TCHAR> BlackPieceClassToFenChar =
	{
		{AChPawn::StaticClass(), 'p'},
		{AChRook::StaticClass(), 'r'},
		{AChKnight::StaticClass(), 'n'},
		{AChBishop::StaticClass(), 'b'},
		{AChKing::StaticClass(), 'k'},
		{AChQuin::StaticClass(), 'q'}
	};

	// Mapping of white piece classes to their FEN representation characters.
	inline static TMap<UClass*, TCHAR> WhitePieceClassToFenChar =
	{
		{AChPawn::StaticClass(), 'P'},
		{AChRook::StaticClass(), 'R'},
		{AChKnight::StaticClass(), 'N'},
		{AChBishop::StaticClass(), 'B'},
		{AChKing::StaticClass(), 'K'},
		{AChQuin::StaticClass(), 'Q'}
	};

	// Mapping of FEN representation characters to black piece classes.
	inline static TMap<TCHAR, UClass*> FenCharToBlackPieceClass =
	{
		{'p', AChPawn::StaticClass()},
		{'r', AChRook::StaticClass()},
		{'n', AChKnight::StaticClass()},
		{'b', AChBishop::StaticClass()},
		{'k', AChKing::StaticClass()},
		{'q', AChQuin::StaticClass()}
	};

	// Mapping of FEN representation characters to white piece classes.
	inline static TMap<TCHAR, UClass*> FenCharToWhitePieceClass =
	{
		{'P', AChPawn::StaticClass()},
		{'R', AChRook::StaticClass()},
		{'N', AChKnight::StaticClass()},
		{'B', AChBishop::StaticClass()},
		{'K', AChKing::StaticClass()},
		{'Q', AChQuin::StaticClass()}
	};
	
	// Mapping of horizontal indices to UCI characters.
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

	// Mapping of reverse UCI characters to horizontal indices.
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

private:

	// Paths to blueprint classes of chess pieces.
	inline const static FString PawnClass = "/Game/BLueprints/MiniGames/Chess/BP_ChPawn.BP_ChPawn_C";
	inline const static FString RookClass = "/Game/BLueprints/MiniGames/Chess/BP_ChRook.BP_ChRook_C";
	inline const static FString KnightClass = "/Game/BLueprints/MiniGames/Chess/BP_ChKnight.BP_ChKnight_C";
	inline const static FString BishopClass = "/Game/BLueprints/MiniGames/Chess/BP_ChBishop.BP_ChBishop_C";
	inline const static FString KingClass = "/Game/BLueprints/MiniGames/Chess/BP_ChKing.BP_ChKing_C";
	inline const static FString QuinClass = "/Game/BLueprints/MiniGames/Chess/BP_ChQuin.BP_ChQuin_C";
};
