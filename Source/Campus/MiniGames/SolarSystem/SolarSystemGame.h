// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Campus/Interfaces/MiniGames/MiniGames.h"
#include "SolarSystemGame.generated.h"

class ASpaceObject;
class UNiagaraSystem;
class USceneComponent;
class ASpaceObjectSpot;
class UNiagaraComponent;
class UStaticMeshComponent;

UCLASS()
class CAMPUS_API ASolarSystemGame : public AActor, public IMiniGames
{
	GENERATED_BODY()
	
public:	
	ASolarSystemGame();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "SolarSystemSettings")
	ASpaceObject* TheSun;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "SolarSystemSettings")
	TArray<ASpaceObjectSpot*> SpaceObjectSpots;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "SolarSystemSettings")
	UStaticMeshComponent* StaticMeshComponent;

	// UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "SolarSystemSettings")
	// USceneComponent* SceneComponentStars;

	// UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "SolarSystemSettings")
	// USceneComponent* SceneComponentCosmicDust;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "SolarSystemSettings")
	UNiagaraSystem* NiagaraSystemStars;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "SolarSystemSettings")
	UNiagaraSystem* NiagaraSystemCosmicDust;
	
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "SolarSystemSettings")
	UNiagaraComponent* NiagaraComponentStars;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "SolarSystemSettings")
	UNiagaraComponent* NiagaraComponentCosmicDust;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION(meta = (BlueprintProtected = "true"))
	void OnChangeState();

	UFUNCTION(meta = (BlueprintProtected = "true"))
	void StartSystem();
	
	void SpawnVFX(UNiagaraSystem* VFXToSpawn, const FVector& Location, const FVector& SpawnOffset) const;
};
