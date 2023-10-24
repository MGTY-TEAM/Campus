// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerItem.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"


void UServerItem::SetInfo(FString Port, int32 ClientsCount)
{
	PortText->SetText(FText::FromString(Port));
	ClientsCountText->SetText(FText::FromString(FString::FromInt(ClientsCount)));
}

void UServerItem::UpdateClientsCount(int32 ClientsCount)
{
	ClientsCountText->SetText(FText::FromString(FString::FromInt(ClientsCount)));
}

FString UServerItem::GetPort()
{
	return PortText->GetText().ToString();
}

void UServerItem::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	ConnectButton->OnClicked.AddDynamic(this, &UServerItem::OnConnectionButtonClicked);
}

void UServerItem::OnConnectionButtonClicked()
{
	OnFormExecute.Broadcast(PortText->GetText().ToString());
}