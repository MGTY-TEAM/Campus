// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "Campus/AI/AIDrone/CampusCoreTypes.h"
#include "CatchMessageService.generated.h"

class AAIAnimDrone;
class UMessageInstance;

UCLASS()
class CAMPUS_API UCatchMessageService : public UBTService
{
	GENERATED_BODY()
	
protected:
	virtual void OnSearchStart(FBehaviorTreeSearchData& SearchData) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	EActionType SActionType = EActionType::Walk;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector SelfActorKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector ActionTypeKey;
private:
	bool FirstTick = true;

	UFUNCTION()
	void MessageSent(UMessageInstance* MessageInstance);

	AAIAnimDrone* Drone;
	UBlackboardComponent* Blackboard;
};
