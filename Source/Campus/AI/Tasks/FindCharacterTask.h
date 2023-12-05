// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Navigation/PathFollowingComponent.h"
#include "FindCharacterTask.generated.h"

class UNavigationSystemV1;

UCLASS()
class CAMPUS_API UFindCharacterTask : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UFindCharacterTask();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector SelfActorKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector CharacterActorKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector LastLocationKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector ISeeYouKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (ClampMin = "2.0", ClampMax = "60.0"))
	float WaitingTime = 15.0f;

private:
	ANavigationData* FindNavigationData(UNavigationSystemV1& NavSys, UObject* Owner) const;

	UPROPERTY(EditDefaultsOnly, Category = Pathfinding)
	TSubclassOf<UNavigationQueryFilter> FilterClass;

	FAIRequestID MainRequestID;

	bool IsMove = false;
	bool IsMoving() const { return IsMove; }
	void FinishMove(const FAIRequestID RequestID, const FPathFollowingResult& Result);

	EBTNodeResult::Type RequestMove(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	void AbortMove(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

	FTimerHandle CharacterLossHandle;
	void OnTimerFired();

	UBehaviorTreeComponent* OwnerComponent;
	uint8* NodeMem;
};
