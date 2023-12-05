// Fill out your copyright notice in the Description page of Project Settings.


#include "Campus/Widgets/InteractionWidget.h"
#include "Campus/Core/BaseCharacter/BaseFirstPersonCharacter.h"
#include "Campus/AI/Tasks/MoveAlongThePathTask.h"
#include "Campus/AI/AIDroneController.h"
#include "Navigation/PathFollowingComponent.h"
#include "AITypes.h"
#include "Engine/Engine.h"

void UInteractionWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	
}

bool UInteractionWidget::CanHelp()
{
	// GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Red, "Can Interact");
	const auto Controller = GetOwningPlayer();
	if (!Controller) return false;

	const auto Character = Cast<ABaseFirstPersonCharacter>(Controller->GetPawn());
	if (!Character) return false;

	return Character->CanInteract() || bCanInteract;
}

bool UInteractionWidget::NeedHelpAfterArrived()
{
	const auto Controller = GetOwningPlayer();
	if (!Controller) return false;

	const auto Character = Cast<ABaseFirstPersonCharacter>(Controller->GetPawn());
	if (!Character) return false;

	if (Character->GetArrivalValue()) bCanInteract = true;
	else bCanInteract = false;

	return Character->GetArrivalValue();
}

bool UInteractionWidget::CanInteract()
{
	const auto Controller = GetOwningPlayer();
	if (!Controller) return false;

	const auto Character = Cast<ABaseFirstPersonCharacter>(Controller->GetPawn());
	if (!Character) return false;

	return Character->CanInteract();
}


