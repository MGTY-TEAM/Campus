// Fill out your copyright notice in the Description page of Project Settings.


#include "Campus/AI/Decorators/IsItTrueDecorator.h"
#include "BehaviorTree/BlackboardComponent.h"

UIsItTrueDecorator::UIsItTrueDecorator()
{
	NodeName = "Is It True?";
}

bool UIsItTrueDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Blackboard) return false;

	bool Result = Blackboard->GetValueAsBool(BoolKey.SelectedKeyName);

	if (Result)
	{
		return true;
	}
	else
	{
		return false;
	}
}
