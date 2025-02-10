// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

#include "Campus/UserInterface/Hud/Inventory/UInventoryWidget.h"

UInventoryComponent::UInventoryComponent(): M_InventoryWidget(nullptr)
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInventoryComponent::ConnectInventoryWidget(UUInventoryWidget* InventoryWidget)
{
	if (InventoryWidget && InventoryPool.IsEmpty())
	{
		M_InventoryWidget = InventoryWidget;
	}
}

void UInventoryComponent::SelectNextItem()
{
	if (SelectedInventoryActor)
	{
		if (!SelectedInventoryActor->IsEnabled())
		{
			SelectItem(SelectedInventoryActor);
			return;
		}
		
		if (auto Node = InventoryPool.FindNode(SelectedInventoryActor))
		{
			if (auto NextNode = Node->GetNextNode())
			{
				if (AInventoryActor* NextItem = NextNode->GetValue())
				{
					if (NextItem)
					{
						DeselectItem(SelectedInventoryActor);
						
						SelectedInventoryActor = NextItem;
						
						SelectItem(SelectedInventoryActor);
					}
				}
			}
		}
	}
	else
	{
		if (auto Node = InventoryPool.GetHead())
		{
			if (AInventoryActor* Item = Node->GetValue())
			{
				SelectedInventoryActor = Item;
				SelectItem(SelectedInventoryActor);
			}
		}
	}
}

void UInventoryComponent::SelectPrevItem()
{
	if (SelectedInventoryActor)
	{
		if (auto CurrentNode = InventoryPool.FindNode(SelectedInventoryActor))
		{
			if (auto PrevNode = CurrentNode->GetPrevNode())
			{
				if (AInventoryActor* PrevItem = PrevNode->GetValue())
				{
					DeselectItem(SelectedInventoryActor);

					SelectedInventoryActor = PrevItem;
					
					SelectItem(SelectedInventoryActor);
				}
			}
			else
			{
				DeselectItem(SelectedInventoryActor);
			}
		}
	}
	else
	{
		if (auto Node = InventoryPool.GetHead())
		{
			if (AInventoryActor* Item = Node->GetValue())
			{
				SelectedInventoryActor = Item;
				SelectItem(Item);
			}
		}
	}
}

void UInventoryComponent::AddItemAndSelect(AInventoryActor* Item)
{
	if (Item)
	{
		if (SelectedInventoryActor)
		{
			DeselectItem(SelectedInventoryActor);
		}
		
		InventoryPool.AddTail(Item);
		SelectedInventoryActor = Item;

		if (M_InventoryWidget)
		{
			M_InventoryWidget->AddItem(Item);
		}
		SelectItem(Item);
	}
}

AInventoryActor* UInventoryComponent::RemoveSelectedItem()
{
	AInventoryActor* RemovedItem = nullptr;
	if (SelectedInventoryActor)
	{
		if (SelectedInventoryActor->IsEnabled())
		{
			RemovedItem = SelectedInventoryActor;
			InventoryPool.RemoveNode(SelectedInventoryActor);
			SelectedInventoryActor = nullptr;

			if (M_InventoryWidget)
			{
				M_InventoryWidget->RemoveItem(RemovedItem);
			}
			return RemovedItem;
		}
	}
	return RemovedItem;
}

bool UInventoryComponent::IsEmpty() const
{
	return InventoryPool.IsEmpty();
}

void UInventoryComponent::SelectItem(AInventoryActor* Item)
{
	if (M_InventoryWidget)
	{
		M_InventoryWidget->SelectItem(Item);
	}
	Item->SetEnabled(true);
	OnSelectedItemChanged.Broadcast(SelectedInventoryActor);
}

void UInventoryComponent::DeselectItem(AInventoryActor* Item)
{
	if (M_InventoryWidget)
	{
		M_InventoryWidget->DeselectItem(Item);
	}
	Item->SetEnabled(false);
}
