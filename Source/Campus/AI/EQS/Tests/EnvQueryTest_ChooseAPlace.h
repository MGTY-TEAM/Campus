// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EnvQueryTest_ChooseAPlace.generated.h"

// class ATeleportationPlane;
class UMessageInstance;

UCLASS()
class CAMPUS_API UEnvQueryTest_ChooseAPlace : public UEnvQueryTest
{
	GENERATED_BODY()
	
public:
	UEnvQueryTest_ChooseAPlace(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test")
	int index = 0;

protected:
	virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget")
	FName SelfActorKeyName = "SelfActor";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector ActionPlaceKey;
};
