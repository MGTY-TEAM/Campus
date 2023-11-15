// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Campus/Pickups/BasePickupableActor.h"
#include "BaseGarbage.generated.h"

class USphereComponent;

UCLASS()
class CAMPUS_API ABaseGarbage : public ABasePickupableActor
{
	GENERATED_BODY()
	
public:
	ABaseGarbage();

	virtual void TakingItem(USceneComponent* SceneComponent) override;
protected:
	UPROPERTY(VisibleAnywhere, Category = "Pickup")
	USphereComponent* CollisionComponent;
};
