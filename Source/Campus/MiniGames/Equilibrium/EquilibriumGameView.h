// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EquilibriumGameView.generated.h"

class AEquilibriumView;

UCLASS()
class CAMPUS_API AEquilibriumGameView : public AActor
{
	GENERATED_BODY()
	
public:	
	AEquilibriumGameView();
	
	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditInstanceOnly, Category="Equilibrium")
	TArray<FString> Cups;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equilibrium")
	TSubclassOf<AEquilibriumView> EquilibriumViewClass;

	UPROPERTY(EditDefaultsOnly, Category = "Equilibrium")
	USceneComponent* SceneComponent;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	 
};
