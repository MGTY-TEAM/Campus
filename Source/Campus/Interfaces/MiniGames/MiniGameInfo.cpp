// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniGameInfo.h"

void UMiniGameInfo::SetupInfo(const FString& NewTitle, const FString& NewDescription)
{
	Title = NewTitle;
	Description = NewDescription;
}
