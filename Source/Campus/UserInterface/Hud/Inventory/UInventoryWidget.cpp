// Fill out your copyright notice in the Description page of Project Settings.


#include "UInventoryWidget.h"

#include "InventoryItemWidget.h"
#include "Campus/Inventory/InventoryActor.h"
#include "Components/HorizontalBox.h"

void UUInventoryWidget::AddItem(AInventoryActor* InventoryActor)
{
	if (InventoryActor && !Items.Contains(InventoryActor))
	{
#ifdef INVENTORY_WIDGET_DEBUG
				UE_LOG(LogInventoryWidget, Warning, TEXT("Trying add item"));
#endif
		if (UTexture2D* InventoryActorImage = InventoryActor->GetRenderTargetTexture())
		{
			
#ifdef INVENTORY_WIDGET_DEBUG
			UE_LOG(LogInventoryWidget, Warning, TEXT("Item texture is valid"));
#endif
			
			if (IsValid(InventoryItemWidgetClass))
			{
				UInventoryItemWidget* InventoryItemWidget = CreateWidget<UInventoryItemWidget>(this, InventoryItemWidgetClass);
				if (InventoryActorImage)
				{
					InventoryItemWidget->SetItemImageTexture(InventoryActorImage);
					HorizontalBox->AddChild(InventoryItemWidget);

#ifdef INVENTORY_WIDGET_DEBUG
					UE_LOG(LogInventoryWidget, Warning, TEXT("Adding Item: %s"), *InventoryActor->GetName());
#endif
					Items.Add(InventoryActor, InventoryItemWidget);
				}
			}
		}
	}
}

void UUInventoryWidget::RemoveItem(AInventoryActor* InventoryActor)
{
	if (InventoryActor && Items.Contains(InventoryActor))
	{
		if (UInventoryItemWidget* InventoryItemWidget = Items[InventoryActor])
		{
			HorizontalBox->RemoveChild(InventoryItemWidget);
			Items.Remove(InventoryActor);
		}
	}
}

void UUInventoryWidget::SelectItem(AInventoryActor* InventoryActor)
{
	if (InventoryActor && Items.Contains(InventoryActor))
	{
		for(auto Item : Items)
		{
			Item.Value->SetSelectedState(false);
		}
		Items[InventoryActor]->SetSelectedState(true);
	}
}
