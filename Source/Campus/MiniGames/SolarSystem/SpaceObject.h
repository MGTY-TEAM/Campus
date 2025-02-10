// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Campus/Inventory/InventoryActor.h"
#include "SpaceObject.generated.h"

class UNiagaraSystem;
class UNiagaraComponent;
class UStaticMeshComponent;

UCLASS()
class CAMPUS_API ASpaceObject : public AInventoryActor
{
	GENERATED_BODY()

public:
	ASpaceObject();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlanetSettings")
	ASpaceObject* CenterOfRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlanetSettings", meta = (ClampMin = "0.0"))
	float Speed = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlanetSettings")
	FVector Axis = FVector(0.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlanetSettings")
	FName NameOfObject = NAME_None;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "SolarSystemSettings")
	UNiagaraSystem* NiagaraSystemExplosion;
	
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "SolarSystemSettings")
	UNiagaraComponent* NiagaraComponentExplosion;
public:	
	virtual void Tick(float DeltaTime) override;

	void StartActive();
	void EndActive();
	
	UFUNCTION(BlueprintCallable)
	void SetCanRotateInTrue() { CanRotate = true; }
	UFUNCTION(BlueprintCallable)
	void SetCanRotateInFalse() { CanRotate = false; }

	UFUNCTION(BlueprintCallable)
	FName GetNameOfObject() const { return NameOfObject; }

	UFUNCTION(BlueprintNativeEvent)
	void ReallocatePlanet();

	virtual void SetEnabled(bool bEnabled) override;

	ASpaceObject* GetCenterOfRotation() const { return CenterOfRotation; }
	void SetOldCenterLocation(const FVector& Location) { OldCenterLocation = Location; }

	UFUNCTION(BlueprintCallable)
	void SetCanPickup(const bool NewCondition) { bCanPickup = NewCondition; }

protected:
	UFUNCTION(BlueprintCallable, meta = (BlueprintProtected = "true"))
	FVector GetBeginPosition() const { return BeginPosition; }
private:
	FTimerHandle ExplosionTimerHandle;
	
	void OrthogonalAxis();
	FVector OldCenterLocation;
	bool CanRotate = false;

	void OnActivateSystem();
	FVector BeginPosition = FVector(0.f);

	void ReallocatePlanet_Implementation();
};
