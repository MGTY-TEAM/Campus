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
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, "Create Event");
	return EBTNodeResult::InProgress;
}

void UWaitForMessageTask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, "Tick");
	if (IsSend) FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}

void UWaitForMessageTask::MessageSent(int i)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, "Message Sent");
	IsSend = true;
}
