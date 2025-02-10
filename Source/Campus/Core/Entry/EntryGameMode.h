// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "EntryGameMode.generated.h"

class UEntryWidget;

UCLASS()
class CAMPUS_API AEntryGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AEntryGameMode();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "WidgetClasses")
	TSubclassOf<UEntryWidget> EntryWidgetClass;
	
	UEntryWidget* M_EntryWidget;

	UFUNCTION()
	void OnEntryWidgetExecute(const FString& Token);
};
