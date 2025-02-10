// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreDrone.h"
#include "../../../Interfaces/Interaction/Interactable.h"
#include "PlayerInteractionDrone.generated.h"

/**
 * 
 */

UCLASS()
class CAMPUS_API APlayerInteractionDrone : public ACoreDrone, public IInteractable
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void Interact() override;
	virtual void EndInteract() override;
	
};
