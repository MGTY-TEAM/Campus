// Fill out your copyright notice in the Description page of Project Settings.


#include "Campus/AI/Tasks/WaitForMessageTask.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Campus/AI/AIDroneController.h"
#include "Campus/AI/AIDrone/CoreDrone/AIAnimDrone.h"
#include "Campus/AI/Services/CatchMessageService.h"
#include "Campus/Chat/Components/ChatUserComponent.h"
#include "Campus/Libraries/Gameplay/BotMessageHandler.h"
#include "Campus/UserInterface/ChatBox.h"
#include "Engine/Engine.h"
#include "Microsoft/AllowMicrosoftPlatformTypes.h"

UWaitForMessageTask::UWaitForMessageTask()
{
	NodeName = "Wait For Message";
	bNotifyTick = false;
	bNotifyTaskFinished = true;
	IsSend = false;
}

EBTNodeResult::Type UWaitForMessageTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	IsSend = false;

	Blackboard = OwnerComp.GetBlackboardComponent();
	if (Blackboard)
	{
		Blackboard->SetValueAsEnum(ActionTypeKey.SelectedKeyName, static_cast<uint8>(SActionType));
	}
	GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, "OnSearchStart");
	
	Drone = Cast<AAIAnimDrone>(Blackboard->GetValueAsObject(DroneActorKey.SelectedKeyName));

	if (Drone)
	{
		DroneController = Cast<AAIDroneController>(Drone->Controller);
		if (DroneController)
		{
			DroneController->GetChatComponent()->OnMessageReceived.AddUObject(this, &UWaitForMessageTask::MessageSent);
		}
		
	}

	return EBTNodeResult::InProgress;
}

void UWaitForMessageTask::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
                                         EBTNodeResult::Type TaskResult)
{

}

void UWaitForMessageTask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	
}

void UWaitForMessageTask::MessageSent(UMessageInstance* MessageInstance)
{
	UE_LOG(LogTemp, Warning, TEXT("Message to bot : %s "), *MessageInstance->GetMessageInfo().Get<2>().ToString());
	
	TPair<int, FString>	HandlerResult = UBotMessageHandler::HandleMessage(MessageInstance->GetMessageInfo().Get<2>().ToString());
		
	ActionPlace = HandlerResult.Key;
	
	if (Drone)
	{
		DroneController->GetChatComponent()->SendMessage("DefaultCharacterName", FText::FromString(HandlerResult.Value));
		
		if (ActionPlace > 0)
		{
			Blackboard->SetValueAsEnum(ActionTypeKey.SelectedKeyName, static_cast<uint8>(EActionType::Leading));
			SActionType = EActionType::Leading;
					
			Blackboard->SetValueAsInt(ActionPlaceKey.SelectedKeyName, ActionPlace);
		}
	}
}
