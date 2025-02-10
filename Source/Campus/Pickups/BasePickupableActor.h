// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePickupableActor.generated.h"

UCLASS()
class CAMPUS_API ABasePickupableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ABasePickupableActor();

	virtual void TakingItem(USceneComponent* SceneComponent);
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	float Velocity = 10.0f;
public:	
	virtual void Tick(float DeltaTime) override;

private:
	bool ItemIsMoving = false;

	USceneComponent* TakenItem = nullptr;
};
