// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestManager.h"
#include "Campus/IncentiveSystem/QuestSystem/Quest.h"

TArray<UQuest*> UQuestManager::Quests = TArray<UQuest*>();

FOnQuestUpdated UQuestManager::OnQuestsUpdated;

void UQuestManager::ClearQuestList()
{
	if(!Quests.IsEmpty())
	{
		Quests.Empty();
	}
}

void UQuestManager::CompleteQuest(const FString& QuestPath)
{
	if(!Quests.IsEmpty())
	{
		for(UQuest* Quest : Quests)
		{
			if(Quest && Quest->QuestID == QuestPath)
			{
				Quest->Complete();	
			}
		}
	}
}

void UQuestManager::UpdateState(const FString& QuestPath)
{
}

void UQuestManager::FillQuests(const TArray<UQuest*> NewQuests)
{
	
}

void UQuestManager::FillQuestsByData(const TArray<FQuestRowBase*> QuestRowBases)
{
	ClearQuestList();
	if(!QuestRowBases.IsEmpty())
	{
		for (FQuestRowBase* QuestRowBase : QuestRowBases)
		{
			if(QuestRowBase)
			{
				if(QuestRowBase->ParentQuestID.IsEmpty())
				{
					if(UQuest* Quest = NewObject<UQuest>())
					{
						Quest->SetupQuestByData(QuestRowBase->SubQuestIDs, QuestRowBase->NextQuestIDs, QuestRowBase->QuestID, QuestRowBase->QuestName, QuestRowBase->QuestDescription, QuestRowBase->ParentQuestID);
						Quests.Add(Quest);
					}
				}
			}
		}
		OnQuestsUpdated.Broadcast(Quests);
	}
}

TArray<UQuest*> UQuestManager::GetQuests()
{
	return Quests;
}

void UQuestManager::UpdateQuestState(UQuest* UpdatedQuest)
{
	OnQuestsUpdated.Broadcast(Quests);
}

