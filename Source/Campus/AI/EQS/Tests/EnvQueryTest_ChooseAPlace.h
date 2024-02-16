// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EnvQueryTest_ChooseAPlace.generated.h"

UCLASS()
class CAMPUS_API UEnvQueryTest_ChooseAPlace : public UEnvQueryTest
{
	GENERATED_BODY()
	
public:
	UEnvQueryTest_ChooseAPlace(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget")
	FName SelfActorKeyName = "SelfActor";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FName ActionPlaceKeyName = "ActionPlace";
};
