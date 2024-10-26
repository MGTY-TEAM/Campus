// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest.h"

#include "QuestManager.h"

void UQuest::QuestCoreSetup(const FString& NewQuestID, const FString& NewQuestName, const FString& NewQuestDescription, const FString& NewParentQuestID)
{
	UE_LOG(LogTemp, Warning, TEXT("Quest created: %s"), *NewQuestName);
	
	QuestID = NewQuestID;
	QuestName = NewQuestName;
	QuestDescription = NewQuestDescription;
	ParentQuestID = NewParentQuestID;
}

void UQuest::Complete()
{
	bCompleted = true;
	QuestProgress = 1.f;
	UQuestManager::UpdateQuestState(this);
}

void UQuest::SetupQuestByData(const TArray<FString>& SubQuestsID, const TArray<FString>& NewNextQuests, const FString& NewQuestID,
                              const FString& NewQuestName, const FString& NewQuestDescription, const FString& NewParentQuestID)
{
	QuestCoreSetup(NewQuestID, NewQuestName, NewQuestDescription, NewParentQuestID);
	
	QuestProgress = 0.f;
	bCompleted = false;
}

void UQuest::SetupQuestByObjectList(TArray<UQuest*> NewSubQuests, TArray<UQuest*> NewNextQuests, const FString& NewQuestID,
                        const FString& NewQuestName, const FString& NewQuestDescription, const FString& NewParentQuestID,
                        float CurrentProgress, bool NewbCompleted)
{
	
	QuestCoreSetup(NewQuestID, NewQuestName, NewQuestDescription, NewParentQuestID);
	
	QuestProgress = CurrentProgress;
	bCompleted = NewbCompleted;
}
