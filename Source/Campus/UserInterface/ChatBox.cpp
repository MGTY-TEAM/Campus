// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatBox.h"

#include "AIAnimDrone.h"
#include "Chat_Message.h"
#include "Campus/Chat/ChatManager.h"
#include "Campus/Chat/Components/ChatUserComponent.h"
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
	ChatUserComponent->OnMessageReceived.AddUObject(this, &UChatBox::ReceiveMessage);

	OwnerChatUserComponent = ChatUserComponent;
}

void UChatBox::ReceiveMessage(UMessageInstance* MessageInstance)
{
	if(GetWorld())
	{
		UE_LOG(LogTemp, Warning, TEXT("Catch Chat from bot message : %s"), *MessageInstance->GetMessageInfo().Get<2>().ToString());
	
		TTuple<FName, FName, FText> MessageInfo = MessageInstance->GetMessageInfo();

		UpdateChatMessages(MessageInfo.Get<2>(),FText::FromName(MessageInfo.Get<0>()));
	}
	
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
	SendMessage_TextBox->SetClearKeyboardFocusOnCommit(true);
	
	if (Cast<AAIAnimDrone>(UGameplayStatics::GetActorOfClass(GetWorld(), AAIAnimDrone::StaticClass()))) {
		Drone = Cast<AAIAnimDrone>(UGameplayStatics::GetActorOfClass(GetWorld(), AAIAnimDrone::StaticClass()));

		UHTTPAiMyLogicRequestsLib::AIMyLogicGetRequest(
			[this](const FString& Message, const FString& ActionType, const int ActionID)
			{
				UpdateChatMessages(FText::FromString(Message), FText::FromString("Bot"));
				UE_LOG(LogTemp, Warning, TEXT("SetRequest"));
			}, "/start", Drone->BotURL);
	}
	return true;
}

void UChatBox::NativeConstruct()
{
	SendMessage_TextBox->OnTextCommitted.AddDynamic(this, &UChatBox::OnTextBoxTextCommitted);
	Super::NativeConstruct();
}

void UChatBox::NativeDestruct()
{
	Super::NativeDestruct();
	UE_LOG(LogTemp, Warning, TEXT("WidgetDestroyed"));
}

void UChatBox::OnTextBoxTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod == ETextCommit::OnEnter && !Text.IsEmpty())
	{
		if (OwnerChatUserComponent)
		{
			OwnerChatUserComponent->SendMessage("Bot", Text);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("PlayerChatBox IS DEAD"));
		}
		UpdateChatMessages(Text, FText::FromString("DefaultCharacterName"));
	}

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(),0);
	PlayerController->SetInputMode(FInputModeGameOnly());
}

void UChatBox::UpdateChatMessages(FText Message, FText Sender)
{
	if(APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		
		UChat_Message* WidgetInstance = CreateWidget<UChat_Message>(PlayerController,
	                                                            BlueprintWidgetClass);
		Chat_ScrollBox->ScrollToEnd();
	
		if (WidgetInstance)
		{
			WidgetInstance->AddToViewport();
			
			Chat_ScrollBox->AddChild(WidgetInstance);
		
			WidgetInstance->Message->SetText(Message);
			WidgetInstance->Sender->SetText(Sender);
			SendMessage_TextBox->SetText(FText::GetEmpty());
		}
	}
}

