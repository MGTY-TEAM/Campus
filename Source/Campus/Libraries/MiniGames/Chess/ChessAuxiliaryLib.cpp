// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessAuxiliaryLib.h"

TTuple<int, int, int, int> UChessAuxiliaryLib::FromUCIToCoord(const FString& UCI)
{
	FString FirstKey = "";
	FirstKey += UCI[0];
	int32 IFirst = RverseHorisontalUCI[FirstKey];
	int32 JFirst = FCString::Atoi(*UCI.Mid(1, 1)) - 1;

	FString SecondKey = "";
	SecondKey += UCI[2];
	int32 ISecond = RverseHorisontalUCI[SecondKey];
	int32 JSecond = FCString::Atoi(*UCI.Mid(3, 1)) - 1;

	return TTuple<int, int, int, int>(JFirst, IFirst, JSecond, ISecond);
}
