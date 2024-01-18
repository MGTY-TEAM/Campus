// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Campus/AI/AIDrone/CampusCoreTypes.h"
#include "DefineActionTask.generated.h"

UCLASS()
class CAMPUS_API UDefineActionTask : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UDefineActionTask();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	EActionType ActionType = EActionType::Teleport;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector ActionTypeKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector StartLocationKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector BoolNotTheFirstKey;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
