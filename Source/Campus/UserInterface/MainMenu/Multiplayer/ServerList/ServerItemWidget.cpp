// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerItemWidget.h"

#include "Components/Button.h"
void UServerItemWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ConnectButton->OnClicked.AddDynamic(this, &UServerItemWidget::OnConnectButtonClicked);
}

void UServerItemWidget::OnConnectButtonClicked()
{
		
}
