// Fill out your copyright notice in the Description page of Project Settings.


#include "Campus/AI/EQS/Tests/EnvQueryTest_IfItMovesItFits.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_VectorBase.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Campus/Core/CharacterSystem/BaseCharacter.h"
#include "Engine/Engine.h"

UEnvQueryTest_IfItMovesItFits::UEnvQueryTest_IfItMovesItFits(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer)
{
	Cost = EEnvTestCost::Low;
	ValidItemType = UEnvQueryItemType_VectorBase::StaticClass();
	SetWorkOnFloatValues(false);
}

void UEnvQueryTest_IfItMovesItFits::RunTest(FEnvQueryInstance& QueryInstance) const
{
	const auto DataOwner = Cast<AActor>(QueryInstance.Owner.Get());
	BoolValue.BindData(DataOwner, QueryInstance.QueryID);
	const bool Switch = BoolValue.GetValue();

	UBlackboardComponent* const Blackboard = UAIBlueprintHelperLibrary::GetBlackboard(DataOwner);
	if (!Blackboard) return;

	const auto Character = Cast<ABaseCharacter>(Blackboard->GetValueAsObject(CharacterActorKeyName));

	if (!Character)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, "Wrong");
		return;
	}

	for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
	{
		It.SetScore(TestPurpose, FilterType, Character->GetVelocity().Length() > 0.f, Switch);
	}
}
