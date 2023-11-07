

// Fill out your copyright notice in the Description page of Project Settings.


#include "Campus/AI/Tasks/TeleportTask.h"
#include "Campus/UserInterface/ChatBox.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Campus/AI/AIDrone/CoreDrone/AIAnimDrone.h"

UTeleportTask::UTeleportTask()
{
	NodeName = "Teleport";
}

EBTNodeResult::Type UTeleportTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Blackboard) EBTNodeResult::Failed;

	AAIAnimDrone* Drone = Cast<AAIAnimDrone>(Blackboard->GetValueAsObject(DroneActorKey.SelectedKeyName));
	if (!Drone) return EBTNodeResult::Failed;

	UChatBox* ChatWidget = Cast<UChatBox>(Blackboard->GetValueAsObject(ChatWidgetKey.SelectedKeyName));
	if (!ChatWidget) return EBTNodeResult::Failed;

	TimerDel.BindUObject(Drone, &AAIAnimDrone::TeleportToLocation, ChatWidget->ActionPlace);
	GetWorld()->GetTimerManager().SetTimer(TeleportTimer, TimerDel, 1.f, false);
	Drone->DarkeningScreen();

	return EBTNodeResult::Succeeded;
}
