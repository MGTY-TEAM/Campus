// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Campus/IncentiveSystem/QuestSystem/Quest.h"
#include "QuestsAssigner.generated.h"

UINTERFACE()
class UQuestsAssigner : public UInterface
{
	GENERATED_BODY()
};

class CAMPUS_API IQuestsAssigner
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interaction System")
	void UpdateQuestList(const TArray<UQuest*>& Quests); 
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interaction System")
	void LoadQuestList(const TArray<UQuest*>& Quests);
};
