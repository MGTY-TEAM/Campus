// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SubInteractable.generated.h"

// This class does not need to be modified.
UINTERFACE()
class USubInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CAMPUS_API ISubInteractable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Interact(UActorComponent* InteractComponent, const FVector& InteractPoint, const FVector& InteractionNormal) = 0;
};
