// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Campus/AI/AIDrone/CampusCoreTypes.h"
#include "WaitForMessageTask.generated.h"

class AAIDroneController;
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
	AAIDroneController* DroneController;
	int32 ActionPlace = 0;
	
	UBlackboardComponent* Blackboard;
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	EActionType SActionType = EActionType::Holding;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector SelfActorKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector ActionTypeKey;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector DroneActorKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector CharacterActorKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector ChatWidgetKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector ActionPlaceKey;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
