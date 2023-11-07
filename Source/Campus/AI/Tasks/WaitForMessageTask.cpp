// Fill out your copyright notice in the Description page of Project Settings.


#include "Campus/AI/Tasks/WaitForMessageTask.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Campus/AI/AIDrone/CoreDrone/AIAnimDrone.h"
#include "Campus/UserInterface/ChatBox.h"
#include "Engine/Engine.h"

UWaitForMessageTask::UWaitForMessageTask()
{
	NodeName = "Wait For Message";
	bNotifyTick = true;
}

EBTNodeResult::Type UWaitForMessageTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	IsSend = false;

	const UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Blackboard) EBTNodeResult::Failed;

	UChatBox* ChatWidget = Cast<UChatBox>(Blackboard->GetValueAsObject(ChatWidgetKey.SelectedKeyName));
	if (!ChatWidget) return EBTNodeResult::Failed;
	
	if (ChatWidget && !TeleportationEventExist)
	{
		ChatWidget->TeleportationEvent.AddDynamic(this, &UWaitForMessageTask::MessageSent);
		TeleportationEventExist = true;
	}

	return EBTNodeResult::InProgress;
}

void UWaitForMessageTask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if (IsSend) FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}

void UWaitForMessageTask::MessageSent(int i)
{
	IsSend = true;
}
