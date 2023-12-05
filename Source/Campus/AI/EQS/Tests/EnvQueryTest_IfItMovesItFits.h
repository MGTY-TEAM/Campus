// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EnvQueryTest_IfItMovesItFits.generated.h"

class ABaseFirstPersonCharacter;

UCLASS()
class CAMPUS_API UEnvQueryTest_IfItMovesItFits : public UEnvQueryTest
{
	GENERATED_BODY()
	
public:
	UEnvQueryTest_IfItMovesItFits(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character")
	FName CharacterActorKeyName = "Character";
protected:
	virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;
};
