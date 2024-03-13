// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "PickupSocketComponent.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnPickupPlaced, AInventoryActor*, InventoryActor);
DECLARE_DYNAMIC_DELEGATE(FOnPickupRemoved);

class AInventoryActor;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CAMPUS_API UPickupSocketComponent : public UBoxComponent
{
	GENERATED_BODY()

public:
	UPickupSocketComponent();

	UFUNCTION(BlueprintCallable, Category="Attachment")
	bool CanPlacePickup(AInventoryActor* Actor);
	
	UFUNCTION(BlueprintCallable, Category="Attachment")
	bool PlacePickup(AInventoryActor* Actor);

	UFUNCTION(BlueprintCallable, Category="Attachment")
	bool RemovePickup();

	UFUNCTION(BlueprintCallable, Category="Attachment")
	void SetAttachmentScene(USceneComponent* SceneComponent);

	UFUNCTION(BlueprintCallable)
	bool HasPickup();

	UPROPERTY(EditDefaultsOnly, Category="Attachment")
	FName AttachComponentName;
	
	AActor* GetPickup();
	
	FOnPickupPlaced OnPickupPlaced;
	
	FOnPickupRemoved OnPickupRemoved;
	
protected:
	virtual void BeginPlay() override;
	
	virtual void OnRegister() override;
	
	UPROPERTY(EditDefaultsOnly, Category= "Socket Settings")
	TArray<TSubclassOf<AInventoryActor>> AvailablePickupClasses;

	UPROPERTY(EditDefaultsOnly, Category= "Socket Settings")
	USceneComponent* AttachmentScene;


	USceneComponent* GetAttachComponent() const;

	void PlacePickupOnComponent(USceneComponent* Component);
	
private:
	AInventoryActor* PlacedActor;
};
