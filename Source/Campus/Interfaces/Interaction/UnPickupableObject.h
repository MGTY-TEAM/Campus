// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UnPickupableObject.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UUnPickupableObject : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CAMPUS_API IUnPickupableObject
{
	GENERATED_BODY()

public:
	virtual void UnPickupOn(AActor* Character) = 0;

	virtual void UnPickupOff() = 0;
};
