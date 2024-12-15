// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskWidget.h"

/*#include "Components/CheckBox.h"
#include "Components/TextBlock.h"

void UTaskWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UTaskWidget::SetTaskText(const FString& Text)
{
	if(TaskText)
	{
		TaskText->SetText(FText::FromString(Text));
	}
}

void UTaskWidget::SetTaskState(bool State)
{
	if(TaskStateBox)
	{
		TaskStateBox->SetCheckedState(State ? ECheckBoxState::Checked : ECheckBoxState::Unchecked);
	}
}

void UTaskWidget::SetTaskID(uint16 ID)
{
	TaskID = ID;
}

void UTaskWidget::SetupTask(const FString& TaskText, bool State, uint16 ID)
{
	SetTaskText(TaskText);
	SetTaskState(State);
	SetTaskID(ID);
}

FString UTaskWidget::GetTaskText()
{
	if(TaskText)
	{
		return TaskText->GetText().ToString();
	}
	return FString();
}

bool UTaskWidget::GetTaskState()
{
	if(TaskStateBox)
	{
		switch (TaskStateBox)
		{
			case (ECheckBoxState::Checked):
				return true;
			case (ECheckBoxState::Unchecked):
				return false;
			case (ECheckBoxState::Undetermined):
				return false;
			case default:
				return false;
		}
	}
	return false;
}

uint16 UTaskWidget::GetTaskID()
{
	return TaskID;
}*/
