// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CharacterFocusTask.generated.h"

UCLASS()
class CAMPUS_API UCharacterFocusTask : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UCharacterFocusTask();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector CharacterActorKey;
};
