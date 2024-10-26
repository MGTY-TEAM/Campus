// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestViewController.h"

#include "QuestManager.h"
#include "QuestsAssigner.h"

void UQuestViewController::AddQuestView(UObject* QuestView)
{
	if(QuestView)
	{
		TArray<UQuest*> Quests = UQuestManager::GetQuests();

		for(UQuest* Quest : Quests)
		{
			if(Quest)
			{
				UE_LOG(LogTemp, Warning, TEXT("Quest is valid"));
			}
		}
		IQuestsAssigner::Execute_LoadQuestList(QuestView, UQuestManager::GetQuests());
		QuestViews.Add(QuestView);
	}
}

void UQuestViewController::PostInitProperties()
{
	UObject::PostInitProperties();
	
	QuestViews = TArray<UObject*>();

	UQuestManager::OnQuestsUpdated.AddUObject(this, &UQuestViewController::QuestsUpdated);
	
}

void UQuestViewController::QuestsUpdated(TArray<UQuest*> Quests)
{
	if(!QuestViews.IsEmpty())
	{
		for (UObject* QuestView : QuestViews)
		{
			if(QuestView)
			{
				IQuestsAssigner::Execute_UpdateQuestList(QuestView, Quests);
			}
		}
	}
}
