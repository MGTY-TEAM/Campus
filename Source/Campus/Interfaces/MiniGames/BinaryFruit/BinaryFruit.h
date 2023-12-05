// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Campus/Interfaces/MiniGames/MiniGames.h"
#include "UObject/Interface.h"
#include "BinaryFruit.generated.h"


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

	virtual void BinaryTreeI(int32 a,int32 b,int32 c , FString F,FString S,FString T) {};
	
	 FExecute Execute;

	virtual void PanalI(FString a,FString b,FString c) {};
};
