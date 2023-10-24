// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DarkeningScreen.generated.h"

/**
 * 
 */
UCLASS()
class CAMPUS_API UDarkeningScreen : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* ParentPanel;
	UPROPERTY(meta = (BindWidget))
	class UBorder* DarkScreen;
	
};
