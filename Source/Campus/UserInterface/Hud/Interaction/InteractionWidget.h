// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Campus/Core/CharacterSystem/BaseCharacter.h"
#include "Campus/Core/CharacterSystem/LocalComponents/InteractionComponent.h"
#include "InteractionWidget.generated.h"

class UImage;
class UTextBlock;
UCLASS()
class CAMPUS_API UInteractionWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	UTextBlock* HintText;
	UPROPERTY(meta = (BindWidget))
	UImage* KeyImage;
	
	UInteractionComponent* InteractionComponent;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};
