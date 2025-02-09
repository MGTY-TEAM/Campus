// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "IdleAnimationService.generated.h"

UCLASS()
class CAMPUS_API UIdleAnimationService : public UBTService
{
	GENERATED_BODY()
	
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category = "RobotAnimation")
	float Frequency = 1;

	UPROPERTY(EditAnywhere, Category = "RobotAnimation")
	float Amplitude = 0.1;
};
