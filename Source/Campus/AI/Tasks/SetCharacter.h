// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "SetCharacter.generated.h"

/**
 * 
 */
UCLASS()
class CAMPUS_API USetCharacter : public UBTTaskNode
{
	GENERATED_BODY()
public:
	USetCharacter();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector CharacterActorKey;
};
