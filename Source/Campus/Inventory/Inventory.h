// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryItem.h"
#include "UObject/Object.h"
#include "Inventory.generated.h"


DECLARE_MULTICAST_DELEGATE_OneParam(FOnSelectedItemChanged, UInventoryItem*);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnInventoryItemAdded, UInventoryItem*);

class UInventoryWidget;
class UInventoryItemWidget;

class UInventoryItem;
/**
 * 
 */
UCLASS()
class CAMPUS_API UInventory : public UObject
{
	GENERATED_BODY()

	TDoubleLinkedList<UInventoryItem*> Items;

	UInventoryItem* SelectedItem;

	UInventoryWidget* InventoryWidget;

public:
	void ConnectInventoryWidgetWithInventory(UInventoryWidget* InventoryWidget);

	void SelectNextItem();
	void SelectPrevItem();

	void AddItemAndSelect(UInventoryItem* Item);

	void RemoveSelectedItem();

	FOnSelectedItemChanged OnSelectedItemChanged;
	FOnInventoryItemAdded OnInventoryItemAdded;
};
