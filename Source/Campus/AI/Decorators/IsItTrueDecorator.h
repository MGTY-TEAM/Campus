// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "IsItTrueDecorator.generated.h"

UCLASS()
class CAMPUS_API UIsItTrueDecorator : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UIsItTrueDecorator();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector BoolKey;

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;
};
