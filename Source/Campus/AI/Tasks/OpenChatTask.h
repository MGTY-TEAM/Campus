// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "OpenChatTask.generated.h"

class UChatBox;
class AAIAnimDrone;

UCLASS()
class CAMPUS_API UOpenChatTask : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UOpenChatTask();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector DroneActorKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector ChatWidgetKey;

private:
	UChatBox* ChatWidget;
};
