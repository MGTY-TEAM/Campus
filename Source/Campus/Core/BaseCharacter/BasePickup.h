// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Campus/Interfaces/Interaction/Interactable.h"
#include "UObject/Object.h"
#include "BasePickup.generated.h"

/**
 * 
 */
UCLASS()
class CAMPUS_API UBasePickup : public UObject, public IInteractable
{
	GENERATED_BODY()

	UBasePickup();

public:
	virtual void Interact(AActor* InteractedActor, AActor* SelfCharacter) override;
	virtual void EndInteract(AActor* FocusActor, AActor* SelfCharacter) override;
};
