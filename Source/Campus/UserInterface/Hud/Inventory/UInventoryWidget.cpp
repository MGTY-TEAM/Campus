// Fill out your copyright notice in the Description page of Project Settings.


#include "UInventoryWidget.h"

#include "InventoryItemWidget.h"
#include "Campus/Inventory/InventoryActor.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/Image.h"

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
					
					UHorizontalBoxSlot* HorizontalBoxSlot = HorizontalBox->AddChildToHorizontalBox(InventoryItemWidget);

					FSlateChildSize SlateChildSize;
					SlateChildSize.SizeRule = ESlateSizeRule::Automatic;
					SlateChildSize.Value = 1.0f;
					
					HorizontalBoxSlot->SetSize(SlateChildSize);
					
					HorizontalBoxSlot->SetPadding(FMargin(InventoryItemsPadding));

					HorizontalBoxSlot->SetHorizontalAlignment(HAlign_Left);
					HorizontalBoxSlot->SetVerticalAlignment(VAlign_Center);
					
#ifdef INVENTORY_WIDGET_DEBUG
					UE_LOG(LogInventoryWidget, Warning, TEXT("Adding Item: %s"), *InventoryActor->GetName());
#endif
					Items.Add(InventoryActor, InventoryItemWidget);
					ExpandBackGroundImage();
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
			CompressBackGroundImage();
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

void UUInventoryWidget::DeselectItem(AInventoryActor* InventoryActor)
{
	if (InventoryActor && Items.Contains(InventoryActor))
    {
        Items[InventoryActor]->SetSelectedState(false);
    }
}

void UUInventoryWidget::ExpandBackGroundImage()
{
	if (UCanvasPanelSlot* BackGroundImagePanelSlot = Cast<UCanvasPanelSlot>(BackGroundImage->Slot))
	{
		FMargin Offsets = BackGroundImagePanelSlot->GetOffsets();

		FMargin NewOffsets = FMargin(0,0,Offsets.Right + (InventoryItemsSize + InventoryItemsPadding * 2), 0);
		
		BackGroundImagePanelSlot->SetOffsets(NewOffsets);
	}
}

void UUInventoryWidget::CompressBackGroundImage()
{
	if (UCanvasPanelSlot* BackGroundImagePanelSlot = Cast<UCanvasPanelSlot>(BackGroundImage->Slot))
	{
		FMargin Offsets = BackGroundImagePanelSlot->GetOffsets();
	
		FMargin NewOffsets  = FMargin(0,0,Offsets.Right - (InventoryItemsSize + InventoryItemsPadding * 2), 0);

		BackGroundImagePanelSlot->SetOffsets(NewOffsets);
	}
}
