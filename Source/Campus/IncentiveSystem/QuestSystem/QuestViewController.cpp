// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestViewController.h"

#include "QuestManager.h"
#include "QuestsAssigner.h"

UQuestViewController::UQuestViewController()
{
	QuestViews = TArray<TWeakObjectPtr<UObject>>();
	
	UQuestManager::OnQuestsUpdated.AddUObject(this, &UQuestViewController::QuestsUpdated);
}

void UQuestViewController::AddQuestView(TWeakObjectPtr<UObject> QuestView)
{
	if(QuestView.IsValid() && QuestView->GetClass()->ImplementsInterface(UQuestsAssigner::StaticClass()))
	{
		TArray<UQuest*> Quests = UQuestManager::GetQuestPTRs();
		if(!Quests.IsEmpty())
		{
			IQuestsAssigner::Execute_LoadQuestList(QuestView.Get(), Quests);
		}
		QuestViews.Add(QuestView);
	}
}

void UQuestViewController::PostInitProperties()
{
	UObject::PostInitProperties();
}

void UQuestViewController::BeginDestroy()
{
	UObject::BeginDestroy();
	
	if(UQuestManager::OnQuestsUpdated.IsBoundToObject(this))
	{
		UQuestManager::OnQuestsUpdated.RemoveAll(this);
	}
}

void UQuestViewController::QuestsUpdated(TArray<TWeakObjectPtr<UQuest>> Quests)
{
	if(!QuestViews.IsEmpty())
	{
		TArray<UQuest*> QuestPTRs = TArray<UQuest*>();
		for(TWeakObjectPtr<UQuest> QuestPtr : Quests)
		{
			if(QuestPtr.IsValid())
			{
				QuestPTRs.Add(QuestPtr.Get());
			}
		}
		for (TWeakObjectPtr<UObject> QuestView : QuestViews)
		{
			if(QuestView.IsValid())
			{
				IQuestsAssigner::Execute_UpdateQuestList(QuestView.Get(), QuestPTRs);
			}
		}
	}
}
