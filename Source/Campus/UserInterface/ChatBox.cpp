// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatBox.h"

#include "AIAnimDrone.h"
#include "Chat_Message.h"
#include "Campus/Chat/ChatManager.h"
#include "Campus/Chat/ChatUserComponent.h"
#include "Campus/Libraries/Requests/Services/HTTPAiMyLogicRequestsLib.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Types/SlateEnums.h"

/////////////////////
void UChatBox::ConnectChatComponent(UChatUserComponent* ChatUserComponent)
{
	ChatUserComponent->OnMessageReceived.BindUObject(this, &UChatBox::ReceiveMessage);
}

void UChatBox::ReceiveMessage(UMessageInstance* MessageInstance)
{
	TTuple<FName, FName, FText> MessageInfo = MessageInstance->GetMessageInfo();
	MessageInfo.Get<0>();// Получение имени отправителя
	MessageInfo.Get<1>();// Имя Получателя
	MessageInfo.Get<2>();// Сообщение
}
////////////////////
void UChatBox::StartTeleport(int index)
{
	TeleportationEvent.Broadcast(index);
}

void UChatBox::SetFocusOnTextInput()
{
	SendMessage_TextBox->SetKeyboardFocus();
}

bool UChatBox::Initialize()
{
	Super::Initialize();


	if (Cast<AAIAnimDrone>(UGameplayStatics::GetActorOfClass(GetWorld(), AAIAnimDrone::StaticClass())))
	{
		Drone = Cast<AAIAnimDrone>(UGameplayStatics::GetActorOfClass(GetWorld(), AAIAnimDrone::StaticClass()));

		UHTTPAiMyLogicRequestsLib::AIMyLogicGetRequest(
			[this](const FString& Message, const FString& ActionType, const int ActionID)
			{
				SendMessage(FText::FromString(Message), FText::FromString("AI"));
				UE_LOG(LogTemp, Warning, TEXT("SetRequest"));
			}, "/start", Drone->BotURL);
	}
	return true;
}

void UChatBox::OnTextBoxTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod == ETextCommit::OnEnter && !Text.IsEmpty())
	{
		UChatManager::SendChatMessage("Bot", "DefaultCharacterName", Text);
		SendMessage(Text, FText::FromString("DefaultCharacterName"));
	}
}

void UChatBox::NativeConstruct()
{
	//SendMessage_TextBox->OnTextCommitted.AddDynamic(this, &UChatBox::OnTextBoxTextCommitted);
	SendMessage_Button->OnClicked.AddDynamic(this, &UChatBox::SendMessageButtonClicked);
	SendMessage_TextBox->OnTextCommitted.AddDynamic(this, &UChatBox::OnTextBoxTextCommitted);
	
	Super::NativeConstruct();
}

void UChatBox::SendMessageButtonClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("Button pressed"));

	FString StringRequest = SendMessage_TextBox->GetText().ToString();
	if (!StringRequest.IsEmpty())
	{
		UHTTPAiMyLogicRequestsLib::AIMyLogicGetRequest(
			[this](const FString& Message, const FString& ActionType, const int& ActionID)
			{
				BotResponse(Message, ActionType, ActionID);
			}, StringRequest, Drone->BotURL);
		SendMessage(SendMessage_TextBox->GetText(), FText::FromString("User"));
		SendMessage_Button->SetIsEnabled(false);
	}
}


void UChatBox::SendMessage(FText Message, FText Sender)
{
	UChat_Message* WidgetInstance = CreateWidget<UChat_Message>(GetWorld()->GetFirstPlayerController(),
	                                                            BlueprintWidgetClass);

	if (WidgetInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("SendMessage"));
		
		WidgetInstance->AddToViewport();
		
		Chat_ScrollBox->AddChild(WidgetInstance);
		
		WidgetInstance->Message->SetText(Message);
		WidgetInstance->Sender->SetText(Sender);
		SendMessage_TextBox->SetText(FText::GetEmpty());

		UChatManager::SendChatMessage("DefaultCharacterName", "Bot", Message);
	}
}

void UChatBox::BotResponse(const FString& Message, const FString& ActionType, const int& ActionID)
{
	UE_LOG(LogRequests, Log, TEXT("GET Request Result: %s"), *Message);

	SendMessage(FText::FromString(Message), FText::FromString("AI"));
	
	Chat_ScrollBox->ScrollToEnd();
	SendMessage_Button->SetIsEnabled(true);
	
	if (ActionType == "Teleport")
	{
		ActionPlace = ActionID;
		// TeleportationEvent.Broadcast(ActionPlace);
		SendMessageEvent.Broadcast(ActionPlace);
	}
	else if (ActionType == "Walk")
	{
	}
	else if (ActionType == "ViewInfo")
	{
	}
}
