// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "BehaviorTree/BTDecorator.h"
#include "BehaviorTree/Decorators/BTDecorator_Blackboard.h"
#include "IsItTrueDecorator.generated.h"

UCLASS()
class CAMPUS_API UIsItTrueDecorator : public UBTDecorator
{
	GENERATED_BODY()
	
	// AIMODULE_API virtual EBlackboardNotificationResult OnBlackboardKeyValueChange(const UBlackboardComponent& Blackboard, FBlackboard::FKey ChangedKeyID) override;
public:
	UIsItTrueDecorator();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector BoolKey;

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;

	UPROPERTY(Category = FlowControl, EditAnywhere)
	TEnumAsByte<EBTBlackboardRestart::Type> NotifyObserver;
};
