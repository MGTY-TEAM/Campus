// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "WaitForMessageTask.generated.h"

class AAIAnimDrone;
class UMessageInstance;

UCLASS()
class CAMPUS_API UWaitForMessageTask : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UWaitForMessageTask();

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;

	bool TeleportationEventExist = false;
	bool IsSend = false;

	UFUNCTION()
	void MessageSent(UMessageInstance* MessageInstance);

	AAIAnimDrone* Drone;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector DroneActorKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector CharacterActorKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector ChatWidgetKey;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
