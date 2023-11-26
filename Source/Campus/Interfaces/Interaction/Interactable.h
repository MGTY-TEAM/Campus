// Fill out your copyright notice in the Description page of Project Settings.


#pragma once

#include "CoreMinimal.h"
#include "Campus/Core/BaseCharacter/BaseFirstPersonCharacter.h"
#include "Interactable.generated.h"
DECLARE_LOG_CATEGORY_EXTERN(LogInteraction, Log, All);

// This class does not need to be modified.
UINTERFACE()
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

class CAMPUS_API IInteractable
{
	GENERATED_BODY()

public:
	virtual void Interact(AActor* InteractedActor, AActor* SelfCharacter) {}
	
	virtual void Interact(UPrimitiveComponent* GetComponent, ABaseFirstPersonCharacter* SelfCharacter) {}
	bool bCanInteract;

	virtual void EndInteract(AActor* FocusActor, AActor* SelfCharacter) {};
};
