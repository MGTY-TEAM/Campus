// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"

#include "Blueprint/UserWidget.h"
#include "InventoryItem.h"
#include "../UserInterface/HUD/Inventory/InventoryWidget.h"

void UInventory::SelectNextItem() 
{
	if(SelectedItem)
	{
		UInventoryItem* NextItem = Items.FindNode(SelectedItem)->GetNextNode()->GetValue();
		if (NextItem)
		{
			SelectedItem = NextItem;
			
			OnSelectedItemChanged.Broadcast(SelectedItem);
		}
	}
}

void UInventory::SelectPrevItem() 
{
	if (SelectedItem)
	{
		UInventoryItem* PrevItem = Items.FindNode(SelectedItem)->GetPrevNode()->GetValue();
		if (PrevItem)
		{
			SelectedItem = PrevItem;

			OnSelectedItemChanged.Broadcast(SelectedItem);
		}
	}
}

void UInventory::AddItemAndSelect(UInventoryItem* Item)
{
	if (Item)
	{
		Items.AddTail(Item);
		SelectedItem = Item;
	
		OnInventoryItemAdded.Broadcast(Item);
		OnSelectedItemChanged.Broadcast(Item);
	}
}

void UInventory::RemoveSelectedItem()
{
	if(SelectedItem)
	{
		Items.RemoveNode(SelectedItem);
		OnSelectedItemChanged.Broadcast(nullptr);
		
		TDoubleLinkedList<UInventoryItem*>::TDoubleLinkedListNode* NextNode  = Items.FindNode(SelectedItem)->GetNextNode();
		TDoubleLinkedList<UInventoryItem*>::TDoubleLinkedListNode* PrevNode  = Items.FindNode(SelectedItem)->GetPrevNode();

		if (PrevNode->GetValue())
		{
			SelectedItem = PrevNode->GetValue();
			
			OnSelectedItemChanged.Broadcast(SelectedItem);
		}
		else if (NextNode->GetValue())
		{
			SelectedItem = NextNode->GetValue();
			
			OnSelectedItemChanged.Broadcast(SelectedItem);
		}
		
	}
}

void UInventory::ConnectInventoryWidgetWithInventory(UInventoryWidget* PlayersInventoryWidget)
{
	InventoryWidget = PlayersInventoryWidget;
}
