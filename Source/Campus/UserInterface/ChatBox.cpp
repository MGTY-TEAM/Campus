// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatBox.h"
#include "Chat_Message.h"
#include "TimerManager.h"
#include "Campus/Libraries/Requests/Services/HTTPAiMyLogicRequestsLib.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"



void UChatBox::StartTeleport(int index)
{
	TeleportationEvent.Broadcast(index);
}

bool UChatBox::Initialize()
{
	Super::Initialize();
	
	
	if(Cast<ADroneGuide>(UGameplayStatics::GetActorOfClass(GetWorld(), ADroneGuide::StaticClass())))
	{
		Drone = Cast<ADroneGuide>(UGameplayStatics::GetActorOfClass(GetWorld(), ADroneGuide::StaticClass()));
	}
	
		UHTTPAiMyLogicRequestsLib::AIMyLogicGetRequest([this](const FString& Message, const FString& ActionType, const int ActionID)
		{
			SendMessage(FText::FromString(Message), FText::FromString("AI"));
			UE_LOG(LogTemp, Warning, TEXT("SetRequest"));
		}, "/start", Drone->BotURL);
	
	return true;
}

void UChatBox::NativeConstruct()
{
	//SendMessage_TextBox->OnTextCommitted.AddDynamic(this, &UChatBox::OnTextBoxTextCommitted);
	SendMessage_Button->OnClicked.AddDynamic(this, &UChatBox::SendMessageButtonClicked);

	Super::NativeConstruct();
}

void UChatBox::SendMessageButtonClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("Button pressed"));
	
	FString StringRequest = SendMessage_TextBox->GetText().ToString();
	if (StringRequest == "")
	{
		
	}
	else
	{
		UHTTPAiMyLogicRequestsLib::AIMyLogicGetRequest([this](const FString& Message, const FString& ActionType, const int& ActionID)
		{
			BotResponse(Message, ActionType, ActionID);//кал!!!
		}, StringRequest, Drone->BotURL);
			SendMessage(SendMessage_TextBox->GetText(), FText::FromString("User"));
			SendMessage_Button->SetIsEnabled(false);
	}
		
;}

/*void UChatBox::OnTextBoxTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod == ETextCommit::OnEnter)
	{
		UE_LOG(LogTemp, Warning, TEXT("Enter Pressed"));
	}
}*/

void UChatBox::SendMessage(FText Message, FText Sender)
{
	UChat_Message* WidgetInstance = CreateWidget<UChat_Message>(GetWorld()->GetFirstPlayerController(), BlueprintWidgetClass);
	
	if (WidgetInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("SendMessage"));
		WidgetInstance->AddToViewport();
		Chat_ScrollBox->AddChild(WidgetInstance);
		WidgetInstance->Message->SetText(Message);
		WidgetInstance->Sender->SetText(Sender);
		SendMessage_TextBox->SetText(FText::GetEmpty());
	}
}

void UChatBox::BotResponse(const FString& Message, const FString& ActionType, const int& ActionID)
{
	UE_LOG(LogRequests, Log, TEXT("GET Request Result: %s"), *Message);
	
	SendMessage(FText::FromString(Message), FText::FromString("AI"));
	Chat_ScrollBox->ScrollToEnd();
	SendMessage_Button->SetIsEnabled(true);
	if(ActionType == "Teleport")
	{
		ActionPlace = ActionID;
		// TeleportationEvent.Broadcast(ActionPlace);
		SendMessageEvent.Broadcast(ActionPlace);
	}
	else if(ActionType == "Walk")
	{
		
	}
	else if(ActionType == "ViewInfo")
	{
		
	}
}

