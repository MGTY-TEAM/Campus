// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PickupableObject.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UPickupableObject : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CAMPUS_API IPickupableObject
{
	GENERATED_BODY()

public:
	virtual void PickupOn() = 0;

	virtual void PickupOff() = 0;
};
