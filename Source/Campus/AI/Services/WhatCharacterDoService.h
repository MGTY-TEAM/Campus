// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "WhatCharacterDoService.generated.h"

UCLASS()
class CAMPUS_API UWhatCharacterDoService : public UBTService
{
	GENERATED_BODY()

public:
	UWhatCharacterDoService();
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector SelfActorKey;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector CharacterActorKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector IsHeStandingKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector IsHeGettingCloserKey;

	virtual void OnSearchStart(FBehaviorTreeSearchData& SearchData) override;
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	UBlackboardComponent* Blackboard = nullptr;
	const AActor* Character = nullptr;
	const AActor* Drone = nullptr;

	double DistanceLastTick = 0;

	bool IsHeStanding() const;
	bool IsHeGettingCloser();
};
