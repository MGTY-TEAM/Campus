// Fill out your copyright notice in the Description page of Project Settings.


#include "Campus/AI/Tasks/WaitForMessageTask.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Campus/AI/AIDrone/CoreDrone/AIAnimDrone.h"
#include "Campus/Chat/ChatManager.h"
#include "Campus/Chat/ChatUserComponent.h"
#include "Campus/UserInterface/ChatBox.h"
#include "Engine/Engine.h"
#include "Campus/Core/BaseCharacter/BaseFirstPersonCharacter.h"
#include "Campus/Libraries/Requests/Services/HTTPAiMyLogicRequestsLib.h"
#include "Microsoft/AllowMicrosoftPlatformTypes.h"

UWaitForMessageTask::UWaitForMessageTask()
{
	NodeName = "Wait For Message";
	bNotifyTick = true;
	bNotifyTaskFinished = true;
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
		/*ChatWidget->SendMessageEvent.AddDynamic(this, &UWaitForMessageTask::MessageSent);*/
		TeleportationEventExist = true;
	}
	Drone = Cast<AAIAnimDrone>(Blackboard->GetValueAsObject(DroneActorKey.SelectedKeyName));

	if (Drone)
	{
		Drone->ChatUserComponent->OnMessageReceived.BindUObject(this, &UWaitForMessageTask::MessageSent);
	}

	return EBTNodeResult::InProgress;
}

void UWaitForMessageTask::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
                                         EBTNodeResult::Type TaskResult)
{
	const UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Blackboard) return;

	if (!Drone) return;

	ABaseFirstPersonCharacter* Character = Cast<ABaseFirstPersonCharacter>(
		Blackboard->GetValueAsObject(CharacterActorKey.SelectedKeyName));
	if (!Character) return;

	// Drone->CloseChat();
	Drone->UnPickupOff();
	Character->UnPickupOff();
	Drone->LeadingTheCharacter = true;

	if (Drone)
	{
		Drone->ChatUserComponent->OnMessageReceived.BindUObject(this, &UWaitForMessageTask::MessageSent);
	}
}

void UWaitForMessageTask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if (IsSend) FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}

void UWaitForMessageTask::MessageSent(UMessageInstance* MessageInstance)
{
	if (Drone)
	{
		UHTTPAiMyLogicRequestsLib::AIMyLogicGetRequest(
			[this](const FString& Message, const FString& ActionType, const int& ActionID)
			{
				if (!Message.IsEmpty())
				{
					if(ActionType == "Teleport")
					{
						int ActionPlace = ActionID;
					}
					
					UChatManager::SendChatMessage("Bot", "DefaultCharacterName", FText::FromString(Message));
					IsSend = true;
				}
			}, MessageInstance->GetMessageInfo().Get<2>().ToString(), Drone->BotURL);
	}
}
