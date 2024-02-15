// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Campus/Interfaces/MiniGames/MiniGames.h"
#include "UObject/Interface.h"
#include "BinaryFruit.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRandom);
// This class does not need to be modified.
UINTERFACE(BlueprintType)
class UBinaryFruit : public UInterface 
{
	GENERATED_BODY()
};

class CAMPUS_API IBinaryFruit
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:


	virtual void BinaryTreeI(int32 FirstAnswerNumber,int32 SecondAnswerNumber,int32 ThirdAnswerNumber, int32 FirstMeshNumber,int32 SecondMeshNumber,int32 ThirdMeshNumber) {};
	
	FExecute Execute;
	FRandom RandomWork;
	
	virtual void PanalI(int32 FirstMeshNumber,int32 SecondMeshNumber,int32 ThirdMeshNumber) {};
};
