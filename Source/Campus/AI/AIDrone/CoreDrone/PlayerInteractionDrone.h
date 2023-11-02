// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreDrone.h"
#include "Campus/Interfaces/Interaction/UnPickupableObject.h"
#include "PlayerInteractionDrone.generated.h"

/**
 * 
 */

UCLASS()
class CAMPUS_API APlayerInteractionDrone : public ACoreDrone, public IUnPickupableObject
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void UnPickupOn(AActor* Character) override;
	virtual void UnPickupOff() override;
	
};
