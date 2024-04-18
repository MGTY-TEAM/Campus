// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionWidget.h"

#include "Campus/Core/CharacterSystem/BaseCharacter.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UInteractionWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if(ABaseCharacter* Character = Cast<ABaseCharacter>(GetOwningPlayerPawn()))
	{
		InteractionComponent = Character->InteractionComponent;
	}
	
	SetVisibility(ESlateVisibility::Visible);
}

void UInteractionWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	if(InteractionComponent)
	{
		HintText->SetVisibility(InteractionComponent->bLookAtInteractionComponent ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
		KeyImage->SetVisibility(InteractionComponent->bLookAtInteractionComponent ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	}
}
