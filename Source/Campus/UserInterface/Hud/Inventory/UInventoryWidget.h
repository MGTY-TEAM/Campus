// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#define INVENTORY_WIDGET_DEBUG 1

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UInventoryWidget.generated.h"

DEFINE_LOG_CATEGORY_STATIC(LogInventoryWidget, Log, Log);

class AInventoryActor;
class UInventoryItemWidget;
class UHorizontalBox;
/**
 * 
 */
UCLASS()
class CAMPUS_API UUInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void AddItem(AInventoryActor* InventoryActor);
	void RemoveItem(AInventoryActor* InventoryActor);

	void SelectItem(AInventoryActor* InventoryActor);

protected:
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UHorizontalBox* HorizontalBox;

	UPROPERTY(EditDefaultsOnly, Category="InventoryClasses")
	TSubclassOf<UInventoryItemWidget> InventoryItemWidgetClass;
	
private:
	TMap<AInventoryActor*, UInventoryItemWidget*> Items;
};
