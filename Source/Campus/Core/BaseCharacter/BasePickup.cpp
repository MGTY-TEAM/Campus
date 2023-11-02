// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePickup.h"

#include "BaseFirstPersonCharacter.h"
#include "Campus/Interfaces/Interaction/UnPickupableObject.h"

void UBasePickup::Interact(AActor* InteractedActor, AActor* SelfCharacter)
{
	IUnPickupableObject* InteractableActor = Cast<IUnPickupableObject>(InteractedActor);
	IUnPickupableObject* InteractableCharacter = Cast<IUnPickupableObject>(SelfCharacter);
	if(InteractableActor && InteractableCharacter)
	{
		InteractableActor->UnPickupOn(SelfCharacter);
		InteractableCharacter->UnPickupOn(SelfCharacter);
		UE_LOG(LogTemp, Error, TEXT("BaseInteractOn"));
		Cast<ABaseFirstPersonCharacter>(SelfCharacter)->bIsFirstInteraction = false;
	}
}

void UBasePickup::EndInteract(AActor* FocusActor, AActor* SelfCharacter)
{
	IUnPickupableObject* InteractableActor = Cast<IUnPickupableObject>(FocusActor);
	IUnPickupableObject* InteractableCharacter = Cast<IUnPickupableObject>(SelfCharacter);
	if(InteractableActor && InteractableCharacter)
	{
		InteractableActor->UnPickupOff();
		InteractableCharacter->UnPickupOff();
		UE_LOG(LogTemp, Error, TEXT("InteractOff"));
		Cast<ABaseFirstPersonCharacter>(SelfCharacter)->bIsFirstInteraction = true;
	}
}
