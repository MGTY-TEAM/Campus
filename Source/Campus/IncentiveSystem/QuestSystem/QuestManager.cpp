#include "QuestManager.h"

#include "Campus/IncentiveSystem/QuestSystem/Quest.h"
#include "Data/QuestRowBase.h"

TArray<TWeakObjectPtr<UQuest>> UQuestManager::Quests = TArray<TWeakObjectPtr<UQuest>>();

FOnQuestUpdated UQuestManager::OnQuestsUpdated;

void UQuestManager::ClearQuestList()
{
	if (!Quests.IsEmpty())
	{
		Quests.Empty();
	}

	if (OnQuestsUpdated.IsBound())
	{
		OnQuestsUpdated.Broadcast(Quests);
	}
}

void UQuestManager::CompleteQuest(const FString& QuestPath)
{
	if (!Quests.IsEmpty())
	{
		for (TWeakObjectPtr<UQuest> WeakQuest : Quests)
		{
			UE_LOG(LogTemp, Warning, TEXT("Quests Num: %i"), Quests.Num());
			if (WeakQuest.IsValid())
			{
				if(WeakQuest->QuestID == QuestPath)
				{
					WeakQuest->Complete();
					break;
				}
			}
		}
	}
}

void UQuestManager::UpdateState(const FString& QuestPath)
{
	// Реализация метода обновления состояния квеста
}

void UQuestManager::FillQuests(TArray<UQuest*> NewQuests)
{
	ClearQuestList();

	if(!NewQuests.IsEmpty())
	{
		for(UQuest* Quest : NewQuests)
		{
			if(Quest)
			{
				TWeakObjectPtr<UQuest> WeakQuest = Quest;
				Quests.Add(WeakQuest);
			}
		}
	}
	
	if(OnQuestsUpdated.IsBound())
	{
		OnQuestsUpdated.Broadcast(Quests);
	}
}

void UQuestManager::FillQuestsByData(const TArray<FQuestRowBase*> QuestRowBases)
{
	ClearQuestList();
	if (!QuestRowBases.IsEmpty())
	{
		for (FQuestRowBase* QuestRowBase : QuestRowBases)
		{
			if (QuestRowBase)
			{
				if (QuestRowBase->ParentQuestID.IsEmpty())
				{
					if (UQuest* Quest = NewObject<UQuest>())
					{
						Quest->SetupQuestByData(QuestRowBase->SubQuestIDs, QuestRowBase->NextQuestIDs, QuestRowBase->QuestID, QuestRowBase->QuestName, QuestRowBase->QuestDescription, QuestRowBase->ParentQuestID);
						TWeakObjectPtr<UQuest> WeakQuestPtr = Quest;
						Quests.Add(WeakQuestPtr);
					}
				}
			}
		}
		if(OnQuestsUpdated.IsBound())
		{
			OnQuestsUpdated.Broadcast(Quests);
		}
	}
}

TArray<TWeakObjectPtr<UQuest>> UQuestManager::GetQuests()
{
	return Quests;
}

TArray<UQuest*> UQuestManager::GetQuestPTRs()
{
	TArray<UQuest*> QuestsPTRs = TArray<UQuest*>();
	for(TWeakObjectPtr<UQuest> WeakQuest : Quests)
	{
		if(WeakQuest.IsValid())
		{
			QuestsPTRs.Add(WeakQuest.Get());
		}
	}
	return QuestsPTRs;
}

void UQuestManager::UpdateQuestState(TWeakObjectPtr<UQuest> UpdatedQuest)
{
	if(OnQuestsUpdated.IsBound())
	{
		OnQuestsUpdated.Broadcast(Quests);
	}
}

