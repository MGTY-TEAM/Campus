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
		ItemImage->Brush.OutlineSettings.Width = 5.0f;
    }
    else
    {
    	ItemImage->Brush.OutlineSettings.Width = 0.0f;
    }
}
