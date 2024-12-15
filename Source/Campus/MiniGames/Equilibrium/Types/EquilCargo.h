// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Campus/Inventory/InventoryActor.h"
#include "EquilCargo.generated.h"

UCLASS()
class CAMPUS_API AEquilCargo : public AInventoryActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Equilibrium")
	int32 Weight;

public:
	int32 GetWeight() const { return Weight; }
};
