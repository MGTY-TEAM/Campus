// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "PickupSocketComponent.generated.h"


class AInventoryActor;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CAMPUS_API UPickupSocketComponent : public UBoxComponent
{
	GENERATED_BODY()

public:
	UPickupSocketComponent();

	UFUNCTION(BlueprintCallable, Category="Attachment")
	bool CanPlacePickup(AActor* Actor);
	
	UFUNCTION(BlueprintCallable, Category="Attachment")
	bool PlacePickup(AActor* Actor);

	UFUNCTION(BlueprintCallable, Category="Attachment")
	bool RemovePickup(AActor* Actor);

	UFUNCTION(BlueprintCallable, Category="Attachment")
	void SetAttachmentScene(USceneComponent* SceneComponent);

	UFUNCTION(BlueprintCallable)
	bool HasPickup();

	AActor* GetPickup();
	
	
protected:
	virtual void BeginPlay() override;
	
	virtual void OnRegister() override;
	
	UPROPERTY(EditDefaultsOnly, Category= "Socket Settings")
	TArray<TSubclassOf<AInventoryActor>> AvailablePickupClasses;

	UPROPERTY(EditDefaultsOnly, Category= "Socket Settings")
	USceneComponent* AttachmentScene;
	
private:
	AActor* PlacedActor;
};
