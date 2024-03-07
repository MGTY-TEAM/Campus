// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryItemWidget.generated.h"

class UImage;
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
	
	void SetItemImageTexture(UTexture2D* Texture);

	void SetSelectedState(bool bSelected);
private:
};
