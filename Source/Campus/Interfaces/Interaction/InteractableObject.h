// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractableObject.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UInteractableObject : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CAMPUS_API IInteractableObject
{
	GENERATED_BODY()

public:
	virtual void InteractableObjectOn() = 0;

	virtual void InteractableObjectOff() = 0;
};
