// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionWidget.h"

#include "Campus/Core/CharacterSystem/BaseCharacter.h"
#include "Components/TextBlock.h"

void UInteractionWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ABaseCharacter* Character = Cast<ABaseCharacter>(GetOwningPlayerPawn());
	InteractionComponent = Character->InteractionComponent;

	SetVisibility(ESlateVisibility::Visible);
}

void UInteractionWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	if(InteractionComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Interaction Component is valid")); 
		SetVisibility(InteractionComponent->bLookAtInteractionComponent ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	}
}
