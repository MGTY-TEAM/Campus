
#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Campus/IncentiveSystem/QuestSystem/Quest.h"
#include "Data/QuestRowBase.h"
#include "QuestManager.generated.h"


DECLARE_MULTICAST_DELEGATE_OneParam(FOnQuestUpdated, TArray<UQuest*>);

UCLASS()
class CAMPUS_API UQuestManager : public UObject
{
	GENERATED_BODY()
	
	static TArray<UQuest*> Quests;

	static void ClearQuestList();
public:
	static FOnQuestUpdated OnQuestsUpdated;

	UFUNCTION(BlueprintCallable, Category="IncentiveSystem|QuestManager")
	static void CompleteQuest(const FString& QuestPath);
	static void UpdateState(const FString& QuestPath);

	static void FillQuests(TArray<UQuest*> NewQuests);
	static void FillQuestsByData(const TArray<FQuestRowBase*> QuestRowBases);
		
	static TArray<UQuest*> GetQuests();

	static void UpdateQuestState(UQuest* UpdatedQuest);
};
