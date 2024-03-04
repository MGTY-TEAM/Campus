// Fill out your copyright notice in the Description page of Project Settings.


#include "Campus/AI/Tasks/WaitForMessageTask.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Campus/AI/AIDroneController.h"
#include "Campus/AI/AIDrone/CoreDrone/AIAnimDrone.h"
#include "Campus/AI/Services/CatchMessageService.h"
#include "Campus/Chat/ChatManager.h"
#include "Campus/Chat/Components/ChatUserComponent.h"
#include "Campus/UserInterface/ChatBox.h"
#include "Engine/Engine.h"
#include "Campus/Libraries/Requests/Services/HTTPAiMyLogicRequestsLib.h"
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
	
	if (MessageInstance->GetMessageInfo().Get<2>().IsNumeric())
	{
		ActionPlace = FCString::Atoi(*MessageInstance->GetMessageInfo().Get<2>().ToString());
	}
	if (Drone)
	{
		UHTTPAiMyLogicRequestsLib::AIMyLogicGetRequest(
			[this](const FString& Message, const FString& ActionType, const int& ActionID)
			{
				if (!Message.IsEmpty())
				{
					UE_LOG(LogTemp, Warning,TEXT("API Message : %s"), *Message);
					DroneController->GetChatComponent()->SendMessage("DefaultCharacterName", FText::FromString(Message));
					if (ActionType == "Teleport")
					{
						Blackboard->SetValueAsEnum(ActionTypeKey.SelectedKeyName, static_cast<uint8>(EActionType::Leading));
						SActionType = EActionType::Leading;
						
						Blackboard->SetValueAsInt(ActionPlaceKey.SelectedKeyName, ActionPlace);
					}
				}
			}, MessageInstance->GetMessageInfo().Get<2>().ToString(), Drone->BotURL);
	}
}
