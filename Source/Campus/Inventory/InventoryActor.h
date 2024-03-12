// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#define INVENTORY_ACTOR_DEBUG 1

#include "CoreMinimal.h"
#include "Campus/Interfaces/Interaction/Interactable.h"
#include "GameFramework/Actor.h"
#include "InventoryActor.generated.h"

DEFINE_LOG_CATEGORY_STATIC(LogInventoryActor, Log, Log);

UCLASS()
class CAMPUS_API AInventoryActor : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	AInventoryActor();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* SceneComponent;
	
	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Item Image")
	UTexture2D* ItemImageTexture;


public:
	virtual void Tick(float DeltaTime) override;

	virtual void OnConstruction(const FTransform& Transform) override;
	
	UTexture2D* GetRenderTargetTexture() const;
	
	void DetachFromParent();
	//POOL FUNCTIONS
	void SetEnabled(bool bEnabled);
    bool IsEnabled() const;
private:
	bool M_IsEnabled;

	
};
