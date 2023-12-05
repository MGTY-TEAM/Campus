// Fill out your copyright notice in the Description page of Project Settings.


#include "Campus/AI/Decorators/IsItTrueDecorator.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Enum.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_NativeEnum.h"

UIsItTrueDecorator::UIsItTrueDecorator()
{
	NodeName = "Is It True?";
	NotifyObserver = EBTBlackboardRestart::ResultChange;
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

//EBlackboardNotificationResult UIsItTrueDecorator::OnBlackboardKeyValueChange(const UBlackboardComponent& Blackboard, FBlackboard::FKey ChangedKeyID)
//{
//	UBehaviorTreeComponent* BehaviorComp = (UBehaviorTreeComponent*)Blackboard.GetBrainComponent();
//	if (BehaviorComp == nullptr)
//	{
//		return EBlackboardNotificationResult::RemoveObserver;
//	}
//
//	if (BoolKey.GetSelectedKeyID() == ChangedKeyID)
//	{
//		// can't simply use BehaviorComp->RequestExecution(this) here, we need to support condition/value change modes
//
//		const EBTDecoratorAbortRequest RequestMode = (NotifyObserver == EBTBlackboardRestart::ValueChange) ? EBTDecoratorAbortRequest::ConditionPassing : EBTDecoratorAbortRequest::ConditionResultChanged;
//		ConditionalFlowAbort(*BehaviorComp, RequestMode);
//	}
//
//	return EBlackboardNotificationResult::ContinueObserving;
//}