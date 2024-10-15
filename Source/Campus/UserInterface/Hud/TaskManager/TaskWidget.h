// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TaskWidget.generated.h"

class UCheckBox;
class UTextBlock;

UCLASS()
class CAMPUS_API UTaskWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta=(BindWidget))
	UTextBlock* TaskText;

	UPROPERTY(meta=(BindWidget))
	UCheckBox* TaskStateBox;

	uint16 TaskID;
protected:
	virtual void NativeConstruct() override;

public:
	void SetupTask(const FString& TaskText, bool State, uint16 ID);

	void SetTaskState(bool State);

	FString GetTaskText();
	bool GetTaskState();
	uint16 GetTaskID();

private:

	void SetTaskText(const FString& TaskText);
	void SetTaskID(uint16 ID);
};
