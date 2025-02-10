// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerInteractionDrone.h"
#include "DefaultAnimDrone.generated.h"

/**
 * 
 */
UCLASS()
class CAMPUS_API ADefaultAnimDrone : public APlayerInteractionDrone
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Animation")
	float RotationSpeed = 1;
	UPROPERTY(EditAnywhere, Category="Animation")
	float Frequency = 1;
	UPROPERTY(EditAnywhere, Category="Animation")
	float Amplitude = 0.1;

protected:
	FTimerHandle IdleAnimTimer;
	FTimerHandle RotateToPlayerTimer;

	virtual void BeginPlay() override;

	virtual void StartIdleAnim();
	virtual void StopIdleAnim();

	virtual void StartRotateToPlayerAnim();
	virtual void StopRotateToPlayerAnim();
};
