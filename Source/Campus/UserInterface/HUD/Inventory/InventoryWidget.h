// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

class UInventoryItemWidget;
class UHorizontalBox;
/**
 * 
 */
UCLASS()
class CAMPUS_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* InventoryItemsBox;
	
	UPROPERTY(EditDefaultsOnly, Category = "Entry classes")
	TSubclassOf<UInventoryItemWidget> InventoryItemWidgetClass;
};
