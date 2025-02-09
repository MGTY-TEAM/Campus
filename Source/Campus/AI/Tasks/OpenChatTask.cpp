// Fill out your copyright notice in the Description page of Project Settings.


#include "Campus/AI/Tasks/OpenChatTask.h"
#include "Campus/UserInterface/ChatBox.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Campus/AI/AIDrone/CoreDrone/AIAnimDrone.h"

UOpenChatTask::UOpenChatTask()
{
	NodeName = "Open Chat";
}

EBTNodeResult::Type UOpenChatTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Blackboard) return EBTNodeResult::Failed;

	AAIAnimDrone* Drone = Cast<AAIAnimDrone>(Blackboard->GetValueAsObject(DroneActorKey.SelectedKeyName));
	if (!Drone) return EBTNodeResult::Failed;

	if (Drone->DoesHeInteract())
	{
		ChatWidget = Drone->OpenChat();
		Blackboard->SetValueAsObject(ChatWidgetKey.SelectedKeyName, ChatWidget);
	}
	
	return EBTNodeResult::Succeeded;
}
