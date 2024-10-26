// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Quest.generated.h"

class UQuest;
DECLARE_MULTICAST_DELEGATE_OneParam(FOnQuestStateChanged, UQuest*)

/**
 * 
 */
UCLASS(BlueprintType)
class CAMPUS_API UQuest : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UQuest*> SubQuests;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UQuest*>	NextQuests;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString QuestID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString QuestName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString QuestDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ParentQuestID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float QuestProgress;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCompleted;
	
	void QuestCoreSetup(const FString& NewQuestID, const FString& NewQuestName, const FString& NewQuestDescription,
	                    const FString& NewParentQuestID);

public:

	void Complete();
	/**
	 * @brief Call when quest progress changed or is completed
	 */
	FOnQuestStateChanged OnQuestStateChanged;

	/**
	 * @brief This overload calls if quest data constructs by data
	 * @param SubQuestsID Array of children quests
	 * @param NextQuests Next quest to open after this quest to be completed
	 * @param NewQuestID Quest id
	 * @param NewQuestName Quest name
	 * @param NewQuestDescription Quest description
	 * @param NewParentQuestID Parent Quest
	 */
	void SetupQuestByData(const TArray<FString>& SubQuestsID, const TArray<FString>& NewNextQuests, const FString& NewQuestID, 
	                const FString& NewQuestName, const FString& NewQuestDescription, const FString& NewParentQuestID);

	/**
	 * @brief This overload calls if quest data constructs by object list
	 * @param SubQuestsID Array of children quests
	 * @param NextQuests Next quest to open after this quest to be completed
	 * @param NewQuestID Quest id
	 * @param NewQuestName Quest name
	 * @param NewQuestDescription Quest description
	 * @param NewParentQuestID Parent Quest
	 */
	void SetupQuestByObjectList(TArray<UQuest*> NewSubQuests, TArray<UQuest*> NewNextQuests,const FString& NewQuestID,
		const FString& NewQuestName, const FString& NewQuestDescription, const FString& NewParentQuestID, float CurrentProgress, bool NewbCompleted);
};
