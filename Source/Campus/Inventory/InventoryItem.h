﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "InventoryItem.generated.h"

class AInventoryItemVisual;
/**
 * 
 */
UCLASS()
class CAMPUS_API UInventoryItem : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	UStaticMeshComponent* StaticMeshComponent;
};
