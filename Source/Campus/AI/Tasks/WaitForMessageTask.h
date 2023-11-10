// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "WaitForMessageTask.generated.h"

UCLASS()
class CAMPUS_API UWaitForMessageTask : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UWaitForMessageTask();

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	bool TeleportationEventExist = false;
	bool IsSend = false;

	UFUNCTION()
	void MessageSent(int i = 0);
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector DroneActorKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector ChatWidgetKey;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
