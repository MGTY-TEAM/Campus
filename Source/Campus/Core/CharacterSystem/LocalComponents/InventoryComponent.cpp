// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

UInventoryComponent::UInventoryComponent()
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

void UInventoryComponent::SetInventoryActorAttachComponent(USceneComponent* AttachComponent)
{
	InventoryActorAttachComponent = AttachComponent;
}

void UInventoryComponent::SelectNextItem() 
{
	if(SelectedInventoryActor)
	{
		AInventoryActor* NextItem = InventoryPool.FindNode(SelectedInventoryActor)->GetNextNode()->GetValue();
		if (NextItem)
		{
			if (SelectedInventoryActor)
				SelectedInventoryActor->SetEnabled(false);
			
			SelectedInventoryActor = NextItem;

			SelectedInventoryActor->SetEnabled(true);
			
			OnSelectedItemChanged.Broadcast(SelectedInventoryActor);
		}
	}
}

void UInventoryComponent::SelectPrevItem() 
{
	if (SelectedInventoryActor)
	{
		AInventoryActor* PrevItem = InventoryPool.FindNode(SelectedInventoryActor)->GetPrevNode()->GetValue();
		if (PrevItem)
		{
			if (SelectedInventoryActor)
				SelectedInventoryActor->SetEnabled(false);
			
			SelectedInventoryActor = PrevItem;
			
			SelectedInventoryActor->SetEnabled(true);
			
			OnSelectedItemChanged.Broadcast(SelectedInventoryActor);
		}
	}
}

void UInventoryComponent::AddItemAndSelect(AInventoryActor* Item)
{
	if (Item)
	{
		
		if (SelectedInventoryActor)
			SelectedInventoryActor->SetEnabled(false);
		
		Item->AttachToComponent(InventoryActorAttachComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		InventoryPool.AddTail(Item);
		SelectedInventoryActor = Item;
	
		/*OnInventoryItemAdded.Broadcast(Item);*/
		Item->SetEnabled(true);
		OnSelectedItemChanged.Broadcast(Item);
	}
}

void UInventoryComponent::RemoveSelectedItem()
{
	if(SelectedInventoryActor)
	{
		InventoryPool.RemoveNode(SelectedInventoryActor);
		OnSelectedItemChanged.Broadcast(nullptr);
		
		TDoubleLinkedList<AInventoryActor*>::TDoubleLinkedListNode* NextNode  = InventoryPool.FindNode(SelectedInventoryActor)->GetNextNode();
		TDoubleLinkedList<AInventoryActor*>::TDoubleLinkedListNode* PrevNode  = InventoryPool.FindNode(SelectedInventoryActor)->GetPrevNode();

		if (PrevNode->GetValue())
		{
			SelectedInventoryActor = PrevNode->GetValue();
			
			OnSelectedItemChanged.Broadcast(SelectedInventoryActor);
		}
		else if (NextNode->GetValue())
		{
			SelectedInventoryActor = NextNode->GetValue();
			
			OnSelectedItemChanged.Broadcast(SelectedInventoryActor);
		}
	}
}

