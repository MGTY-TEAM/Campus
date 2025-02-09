// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Campus/Interfaces/MiniGames/MiniGames.h"
#include "Campus/Interfaces/Interaction/Interactable.h"
#include "SolarSystemGame.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStartUniverse);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDestroyUniverse);

class ASpaceObject;
class UNiagaraSystem;
class USceneComponent;
class ASpaceObjectSpot;
class UNiagaraComponent;
class UStaticMeshComponent;

UCLASS()
class CAMPUS_API ASolarSystemGame : public AActor, public IMiniGames, public IInteractable
{
	GENERATED_BODY()
	
public:	
	ASolarSystemGame();

	FOnStartUniverse OnStartUniverse;
	FOnDestroyUniverse OnDestroyUniverse;
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "SolarSystemSettings")
	USceneComponent* PlacementSceneComponent;
	
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "SolarSystemSettings")
	ASpaceObject* TheSun;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "SolarSystemSettings")
	TArray<ASpaceObjectSpot*> SpaceObjectSpots;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "SolarSystemSettings")
	UStaticMeshComponent* StaticMeshComponent;
	
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "SolarSystemSettings")
	UStaticMeshComponent* StaticMeshComponentButton;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "SolarSystemSettings")
	UStaticMeshComponent* StaticMeshComponentGlass;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "NiagaraSystemStarsSettings")
	UNiagaraSystem* NiagaraSystemStars;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "NiagaraSystemStarsSettings", meta = (ClampMin = "0.0", ClampMax = "300.0"))
	float SpawnStars = 200.f;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "NiagaraSystemStarsSettings", meta = (ClampMin = "0.0", ClampMax = "10.0"))
	float SpawnFallingStars = 1.f;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "SolarSystemSettings")
	UNiagaraSystem* NiagaraSystemCosmicDust;
	
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "SolarSystemSettings")
	UNiagaraComponent* NiagaraComponentStars;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "SolarSystemSettings")
	UNiagaraComponent* NiagaraComponentCosmicDust;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SolarSystemSettings")
	TArray<AActor*> LampsToOff;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SolarSystemSettings", meta = (ClampMin = "3.0", ClampMax = "10.0"))
	float DeactivateRateStars = 3.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SolarSystemSettings", meta = (ClampMin = "1.0", ClampMax = "10.0"))
	float DeactivateRateFallingStars = 1.5f;
public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	TArray<AActor*> GetLampsToOff() const { return LampsToOff; }

	UFUNCTION(BlueprintNativeEvent)
	void OnGameCompleted();

	UFUNCTION(BlueprintNativeEvent)
	void OnStartUniverseLogic();

	UFUNCTION(BlueprintNativeEvent)
	void OnDestroyUniverseLogic();

private:
	bool bIsGameCompleted = false;
	bool bIsSystemWorking = false;
	bool bIsInvisible = false;

	UFUNCTION(BlueprintCallable, meta = (BlueprintProtected = "true"))
	void SetInvisibleProperty(const bool NewCondition) { bIsInvisible = NewCondition; } ;
	
	UFUNCTION(meta = (BlueprintProtected = "true"))
	void OnChangeState();

	UFUNCTION(meta = (BlueprintProtected = "true"))
	void StartSystem();

	UFUNCTION(meta = (BlueprintProtected = "true"))
	void DestroySystem();
	
	void SpawnVFX(UNiagaraSystem* VFXToSpawn, const FVector& Location, const FVector& SpawnOffset) const;
	
	void OnGameCompleted_Implementation() {};
	void OnStartUniverseLogic_Implementation() {};
	void OnDestroyUniverseLogic_Implementation() {};

	virtual void Interact(UActorComponent* InteractComponent, const FVector& InteractPoint, const FVector& InteractionNormal) override;
	virtual void EndInteract_Implementation() override;

	FTimerHandle DeactivateStarsHandle;
	FTimerHandle DeactivateFallingStarsHandle;
	void DeactivateStars();
	void DeactivateFallingStars();

	FRotator NormalRotationOfGlassCase = FRotator();
	FRotator DesiredRotationOfGlassCase = FRotator(0.f);
	bool bIsGlassCaseClose = true;
	void InterpolateGlassCaseMesh(float DeltaTime);
};
