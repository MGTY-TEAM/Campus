// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "QuestViewController.generated.h"

class UQuest;
class IQuestsAssigner;
/**
 * 
 */
UCLASS()
class CAMPUS_API UQuestViewController : public UObject
{
	GENERATED_BODY()

	TArray<TWeakObjectPtr<UObject>> QuestViews;
public:
	UQuestViewController();
	
	void AddQuestView(TWeakObjectPtr<UObject> QuestView);

protected:
	UFUNCTION()
	void QuestsUpdated(TArray<TWeakObjectPtr<UQuest>> Quests);

	virtual void PostInitProperties() override;
	virtual void BeginDestroy() override;
};
