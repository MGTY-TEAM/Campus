// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Campus/Core/BaseCharacter/BasePickup.h"
#include "Campus/Inventory/InventoryItem.h"
#include "GameFramework/Actor.h"
#include "InventoryItemVisual.generated.h"


UCLASS()
class CAMPUS_API AInventoryItemVisual : public AActor, public IInteractable
{
	GENERATED_BODY()
	

public:
	// Sets default values for this actor's properties
	AInventoryItemVisual();
	
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* StaticMeshComponent;
	
	virtual UInventoryItem* PickUp();
protected:

	UInventoryItem* InventoryItem;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Interact(AActor* InteractedActor, AActor* SelfCharacter) override;

	virtual void EndInteract(AActor* FocusActor, AActor* SelfCharacter) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
