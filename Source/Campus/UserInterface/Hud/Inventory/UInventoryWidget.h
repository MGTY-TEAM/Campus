// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#define INVENTORY_WIDGET_DEBUG 1

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UInventoryWidget.generated.h"

DEFINE_LOG_CATEGORY_STATIC(LogInventoryWidget, Log, Log);

class UImage;
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
	void DeselectItem(AInventoryActor* InventoryActor);

protected:
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UImage* BackGroundImage;
	
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UHorizontalBox* HorizontalBox;

	UPROPERTY(EditDefaultsOnly, Category="InventoryClasses")
	TSubclassOf<UInventoryItemWidget> InventoryItemWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category="View Settings", meta = (ClampMin = 0.0f, ClampMax = 20.0f))
	float InventoryItemsPadding = 5.0f;
	UPROPERTY(EditDefaultsOnly, Category="View Settings")
	float InventoryItemsSize = 100.0f;
	
private:
	TMap<AInventoryActor*, UInventoryItemWidget*> Items;

	void ExpandBackGroundImage();
	void CompressBackGroundImage();
};
