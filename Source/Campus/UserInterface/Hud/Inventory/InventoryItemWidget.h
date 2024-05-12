// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Border.h"
#include "InventoryItemWidget.generated.h"

class UImage;
class UBorder;
/**
 * 
 */
UCLASS()
class CAMPUS_API UInventoryItemWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, meta =(BindWidget))
	UImage* ItemImage;

	UPROPERTY(EditDefaultsOnly, meta =(BindWidget))
	UBorder* OutLine;

	FSlateBrush Brush;

	virtual void NativeConstruct() override;
	
	void SetItemImageTexture(UTexture2D* Texture);

	void SetSelectedState(bool bSelected);
private:
};
