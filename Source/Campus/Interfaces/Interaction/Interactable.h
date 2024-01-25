// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */

class CAMPUS_API IInteractable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	virtual void Interact(UActorComponent* InteractComponent, const FVector& InteractPoint, const FVector& InteractionNormal) = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interaction System")
	void BPInteract(const FHitResult& HitResult);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interaction System")
	void HoldInteract(const FHitResult& HitResult);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interaction System")
	void EndInteract();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interaction System")
	void DragInteract(const FHitResult& HitResult);
};
