// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Campus/Inventory/InventoryActor.h"
#include "SpaceObject.generated.h"

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

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetCanRotateInTrue() { CanRotate = true; }
	UFUNCTION(BlueprintCallable)
	void SetCanRotateInFalse() { CanRotate = false; }

	UFUNCTION(BlueprintCallable)
	FName GetNameOfObject() const { return NameOfObject; }

	virtual void SetEnabled(bool bEnabled) override;

	ASpaceObject* GetCenterOfRotation() const { return CenterOfRotation; }
	void SetOldCenterLocation(const FVector& Location) { OldCenterLocation = Location; }

private:
	void OrthogonalAxis();
	FVector OldCenterLocation;
	bool CanRotate = false;
};
