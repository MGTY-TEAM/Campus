// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TaskListWidget.generated.h"

class UVerticalBox;
class UTaskWidget;

UCLASS()
class CAMPUS_API UTaskListWidget : public UUserWidget
{
	GENERATED_BODY()

	TArray<UTaskWidget*> Tasks;

	UPROPERTY(meta =(BindWidget))
	UVerticalBox* TaskContainer;
private:
	virtual void NativeConstruct() override;

public:
	void AddTask(const FString& Task, const bool State, const uint16 ID);
	void CompleteTask(uint16 ID);
	void RemoveTask(uint16 ID);
};
