// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "AIDronePerceptionComponent.generated.h"

UCLASS()
class CAMPUS_API UAIDronePerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()

public:
	AActor* GetInteractionCharacter() const;
};
