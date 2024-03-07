// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItemWidget.h"

#include "Components/Image.h"

void UInventoryItemWidget::SetItemImageTexture(UTexture2D* Texture)
{
	if (Texture)
	{
		ItemImage->SetBrushFromTexture(Texture);
	}
}

void UInventoryItemWidget::SetSelectedState(bool bSelected)
{
	if (bSelected)
    {
		ItemImage->Brush.SetImageSize(ItemImage->GetBrush().GetImageSize() * 1.1);
    }
    else
    {
    	ItemImage->Brush.SetImageSize(ItemImage->GetBrush().GetImageSize() / 1.1);
    }
}
