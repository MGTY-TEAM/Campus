// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

UINTERFACE(Blueprintable)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

class CAMPUS_API IInteractable
{
	GENERATED_BODY()
	
public:
	
	virtual void Interact(UActorComponent* InteractComponent, const FVector& InteractPoint, const FVector& InteractionNormal){};

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interaction System")
	void BPInteract(const FHitResult& HitResult);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interaction System")
	void HoldInteract(const FHitResult& HitResult);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interaction System")
	void EndInteract();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interaction System")
	void DragInteract(const FHitResult& HitResult);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interaction System")
	bool CanInteract();	
};
