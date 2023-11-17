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
	FBlackboardKeySelector DestinationPointKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector ISeeYouKey;

private:
	ANavigationData* FindNavigationData(UNavigationSystemV1& NavSys, UObject* Owner) const;

	UPROPERTY(EditDefaultsOnly, Category = Pathfinding)
	TSubclassOf<UNavigationQueryFilter> FilterClass;

	// FAIRequestID RequestID;

	bool IsMove = false;
	bool IsMoving() const  { return IsMove; }
	void FinishMove(const FAIRequestID RequestID, const FPathFollowingResult& Result);

	bool CharacterIsGone = false;
};
