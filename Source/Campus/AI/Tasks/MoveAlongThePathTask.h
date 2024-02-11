// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Navigation/PathFollowingComponent.h"
#include "MoveAlongThePathTask.generated.h"

class UNavigationSystemV1;

UCLASS()
class CAMPUS_API UMoveAlongThePathTask : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UMoveAlongThePathTask();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector SelfActorKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector CharacterActorKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector DestinationPointKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector ISeeYouKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector IsHeStandingKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector ActionTypeKey;

private:
	FTimerHandle RequestMoveHandle;
	
	ANavigationData* FindNavigationData(UNavigationSystemV1& NavSys, UObject* Owner) const;

	UPROPERTY(EditDefaultsOnly, Category = Pathfinding)
	TSubclassOf<UNavigationQueryFilter> FilterClass;

	FAIRequestID MainRequestID;

	bool IsMove = false;
	bool SetTimer = false;
	bool IsMoving() const  { return IsMove; }
	void FinishMove(const FAIRequestID RequestID, const FPathFollowingResult& Result);

	void ClearTimer();
	void OnRequsetMove();
	EBTNodeResult::Type RequestMove(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	void PauseMove(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;

	UBehaviorTreeComponent* MyOwnerComp;
};
