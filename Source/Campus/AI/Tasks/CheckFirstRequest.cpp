// Fill out your copyright notice in the Description page of Project Settings.


#include "Campus/AI/Tasks/CheckFirstRequest.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Campus/AI/AIDrone/CoreDrone/AIAnimDrone.h"

UCheckFirstRequest::UCheckFirstRequest()
{
	NodeName = "Check First Request";
	bNotifyTick = true;
}

EBTNodeResult::Type UCheckFirstRequest::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Blackboard) EBTNodeResult::Failed;

	bool FirstRequest = !Blackboard->GetValueAsBool(BoolNotTheFirstKey.SelectedKeyName);

	if (FirstRequest)
	{
		Blackboard->SetValueAsBool(BoolNotTheFirstKey.SelectedKeyName, true);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::InProgress;
}

void UCheckFirstRequest::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Blackboard) EBTNodeResult::Failed;

	AAIAnimDrone* Drone = Cast<AAIAnimDrone>(Blackboard->GetValueAsObject(SelfActorKey.SelectedKeyName));
	if (!Drone) return;

	if (Drone->DoesHeInteract()) FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}
