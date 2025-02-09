// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItemWidget.h"

#include "Components/Image.h"

void UInventoryItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Brush.DrawAs = ESlateBrushDrawType::RoundedBox;
	Brush.OutlineSettings.RoundingType = ESlateBrushRoundingType::FixedRadius;
	Brush.OutlineSettings.CornerRadii = FVector4(15.0f, 15.0f, 15.0f, 15.0f);
	Brush.OutlineSettings.Color = FSlateColor(FLinearColor(0.571125f, 0.215861f, 1.0f, 1.0f));
}

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
		Brush.OutlineSettings.Width = 3.0f;
		OutLine->SetBrush(Brush);
		//OutLine->Brush.OutlineSettings.Width = 5.0f;
    }
    else
    {
    	//OutLine->Brush.OutlineSettings.Width = 0.0f;
    	Brush.OutlineSettings.Width = 0.0f;
    	OutLine->SetBrush(Brush);
    }
}
