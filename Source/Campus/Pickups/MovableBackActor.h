// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovableBackActor.generated.h"

UCLASS()
class CAMPUS_API AMovableBackActor : public AActor
{
	GENERATED_BODY()

	FVector StartPosition = FVector();
public:
	// Sets default values for this actor's properties
	AMovableBackActor();
	
	virtual void SlideToStartPosition();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
