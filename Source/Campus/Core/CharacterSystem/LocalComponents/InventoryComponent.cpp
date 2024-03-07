// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

#include "Campus/UserInterface/Hud/Inventory/UInventoryWidget.h"

UInventoryComponent::UInventoryComponent(): M_InventoryWidget(nullptr)
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
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
		if (auto Node = InventoryPool.FindNode(SelectedInventoryActor))
		{
			if (auto NextNode = Node->GetNextNode())
			{
				if (AInventoryActor* NextItem = NextNode->GetValue())
				{
					if (NextItem)
					{
						if (SelectedInventoryActor)
							SelectedInventoryActor->SetEnabled(false);

						SelectedInventoryActor = NextItem;

						SelectedInventoryActor->SetEnabled(true);

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
					if (SelectedInventoryActor)
						SelectedInventoryActor->SetEnabled(false);

					SelectedInventoryActor = PrevItem;

					SelectedInventoryActor->SetEnabled(true);

					SelectItem(SelectedInventoryActor);
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
			SelectedInventoryActor->SetEnabled(false);
		
		InventoryPool.AddTail(Item);
		SelectedInventoryActor = Item;

		/*OnInventoryItemAdded.Broadcast(Item);*/
		Item->SetEnabled(true);
		if(M_InventoryWidget)
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
		RemovedItem = SelectedInventoryActor;
		InventoryPool.RemoveNode(SelectedInventoryActor);
		SelectedInventoryActor = nullptr;

		RemovedItem->SetEnabled(true);

		if (M_InventoryWidget)
		{
			M_InventoryWidget->RemoveItem(RemovedItem);
		}
		return RemovedItem;
	}
	return RemovedItem;
}

bool UInventoryComponent::IsEmpty()
{
	return SelectedInventoryActor != nullptr;
}

void UInventoryComponent::SelectItem(AInventoryActor* Item)
{
	if (M_InventoryWidget)
	{
		M_InventoryWidget->SelectItem(Item);
	}
	OnSelectedItemChanged.Broadcast(SelectedInventoryActor);
}
