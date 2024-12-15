// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "MoveToService.generated.h"

UCLASS()
class CAMPUS_API UMoveToService : public UBTService
{
	GENERATED_BODY()

public:
	UMoveToService();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector NewLocationKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float InterpSpeed = 5;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
