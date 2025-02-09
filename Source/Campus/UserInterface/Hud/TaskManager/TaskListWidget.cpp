// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskListWidget.h"

/*#include "TaskWidget.h"

void UTaskListWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Tasks = TArray<UTaskWidget*>();
}

void UTaskListWidget::AddTask(const FString& Task, const bool State, const uint16 ID)
{
	if(TaskContainer)
	{
		if(UTaskWidget* NewTaskWidget = CreateWidget<UTaskWidget>(GetWorld(), UTaskWidget::StaticClass()))
		{
			Tasks.Add(NewTaskWidget);
			NewTaskWidget->SetupTask(Task, State, ID);
		}
	}
}

void UTaskListWidget::CompleteTask(uint16 ID)
{
	if(Tasks.Num() > 0)
	{
		for(UTaskWidget* Task : Tasks)
		{
			if(Task)
			{
				if(ID == Task->GetTaskID())
				{
					Task->SetTaskState(true);
				}
			}
		}
	}
}

void UTaskListWidget::RemoveTask(uint16 ID)
{
	if(Tasks.Num() > 0)
	{
		for(UTaskWidget* Task : Tasks)
		{
			if(Task)
			{
				if(ID == Task->GetTaskID())
				{
					Tasks.Remove(Task);
					Task->RemoveFromParent();
				}
			}
		}
	}
}*/
