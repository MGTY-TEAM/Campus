// Fill out your copyright notice in the Description page of Project Settings.


#include "Campus/AI/Services/CatchMessageService.h"
#include "Campus/Libraries/Requests/Services/HTTPAiMyLogicRequestsLib.h"
#include "Campus/AI/AIDrone/CoreDrone/AIAnimDrone.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Campus/Chat/ChatUserComponent.h"
#include "Campus\Chat\MessageInstance.h"
#include "Campus/Chat/ChatManager.h"
#include "AIController.h"

void UCatchMessageService::OnSearchStart(FBehaviorTreeSearchData& SearchData)
{
	Blackboard = SearchData.OwnerComp.GetBlackboardComponent();
	if (Blackboard)
	{
		Blackboard->SetValueAsEnum(ActionTypeKey.SelectedKeyName, (uint8)SActionType);
	}
	// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "OnSearchStart");
	AAIController* Controller = SearchData.OwnerComp.GetAIOwner();
	if (Controller)
	{
		Drone = Cast<AAIAnimDrone>(Controller->GetPawn());
		if (Drone)
		{
			Drone->ChatUserComponent->OnMessageReceived.BindUObject(this, &UCatchMessageService::MessageSent);
		}
	}
}

void UCatchMessageService::MessageSent(UMessageInstance* MessageInstance)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, MessageInstance->GetMessageInfo().Get<2>().ToString());
	if (Drone)
	{
		UHTTPAiMyLogicRequestsLib::AIMyLogicGetRequest(
			[this](const FString& Message, const FString& ActionType, const int& ActionID)
			{
				if (!Message.IsEmpty())
				{
					if (ActionType == "Teleport")
					{
						int ActionPlace = ActionID;
						// Blackboard->SetValueAsEnum(ActionTypeKey.SelectedKeyName, (uint8)EActionType::Teleport);
						// SActionType = EActionType::Teleport;
					}

					UChatManager::SendChatMessage("Bot", "DefaultCharacterName", FText::FromString(Message));
				}
			}, MessageInstance->GetMessageInfo().Get<2>().ToString(), Drone->BotURL);
	}
}
