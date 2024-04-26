// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#define INVENTORY_ACTOR_DEBUG 1

#include "CoreMinimal.h"
#include "Campus/Interfaces/Interaction/Interactable.h"
#include "GameFramework/Actor.h"
#include "InventoryActor.generated.h"

class UPickupSocketComponent;
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

	UPROPERTY(EditAnywhere, Category = "Item Image")
	UTexture2D* ItemImageTexture;
	
	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	UAudioComponent* AudioComponent;

	UPROPERTY(EditDefaultsOnly, Category= "Audio")
	USoundBase* DropCue;
	UPROPERTY(EditDefaultsOnly, Category= "Audio")
	USoundBase* PickupCue;

	UPickupSocketComponent* CurrentSocket;
	
public:
	virtual void Tick(float DeltaTime) override;

	virtual void OnConstruction(const FTransform& Transform) override;
	
	UTexture2D* GetRenderTargetTexture() const;

	virtual void PickupProcess();
	virtual void DropProcess();

	virtual void SetAttachSocket(UPickupSocketComponent* socket);
	
	
	//POOL FUNCTIONS
	virtual void SetEnabled(bool bEnabled);
    bool IsEnabled() const;
private:
	bool M_IsEnabled;

	
};
