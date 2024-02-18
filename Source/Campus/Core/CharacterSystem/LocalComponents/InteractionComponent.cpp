// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionComponent.h"

#include "Camera/CameraComponent.h"
#include "..\..\..\Interfaces\Interaction\Interactable.h"
#include "Components/WidgetInteractionComponent.h"

DECLARE_LOG_CATEGORY_CLASS(LogInteractionCompoent, Log, Log);

#define INTERACTION_DEBUG

// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UInteractionComponent::TryInteract()
{
	FHitResult HitResult = GetHitResultByTraceChannel();
	if (AActor* HitActor = HitResult.GetActor())
	{
		
#ifdef  INTERACTION_DEBUG
		UE_LOG(LogInteractionCompoent, Warning, TEXT("%s"), *HitResult.GetActor()->GetName());
#endif
		
		if (IInteractable* Interactable = Cast<IInteractable>(HitActor))
		{
			
#ifdef INTERACTION_DEBUG
			UE_LOG(LogInteractionCompoent, Warning, TEXT("Interact  %s"), *HitActor->GetName());
#endif
			
			Interactable->Interact(HitResult.GetComponent(), HitResult.Location, HitResult.Normal);
			OnSimpleInteract.Broadcast();
		}
		if (HitActor->GetClass()->ImplementsInterface(UInteractable::StaticClass()))
		{
			IInteractable::Execute_BPInteract(HitActor, HitResult);
			OnSimpleInteract.Broadcast();
		}
	}

	if (UWidgetInteractionComponent* WidgetInteractionComponent = Cast<UWidgetInteractionComponent>(
		GetOwner()->GetComponentByClass(UWidgetInteractionComponent::StaticClass())))
	{
#ifdef INTERACTION_DEBUG
		UE_LOG(LogInteractionCompoent, Warning, TEXT("Widget Interaction"));
#endif
		WidgetInteractionComponent->PressPointerKey(EKeys::LeftMouseButton);
		WidgetInteractionComponent->ReleasePointerKey(EKeys::LeftMouseButton);
		//PressKey(EKeys::LeftMouseButton);
	}
}

void UInteractionComponent::SetHoldStatus(bool bStatus)
{
	bInteractHold = bStatus;
}

// Called when the game starts
void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
	if (GetOwner())
	{
		
#ifdef INTERACTION_DEBUG
		UE_LOG(InteractionComponentLog, Warning, TEXT("Owner"));
#endif
		
		if (UCameraComponent* CameraComponent = Cast<UCameraComponent>(
			GetOwner()->GetComponentByClass(UCameraComponent::StaticClass())))
		{
			
#ifdef INTERACTION_DEBUG
			UE_LOG(InteractionComponentLog, Warning, TEXT("Camera"));
#endif
			
			OwnedCameraComponent = CameraComponent;
		}
	}
}

// Called every frame
void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FHitResult HitResult = GetHitResultByTraceChannel();

	if (!bInteractHold)
	{
		FocusActor = HitResult.GetActor();
	}
	else
	{
		if (FocusActor)
		{
			if (FocusActor->GetClass()->ImplementsInterface(UInteractable::StaticClass()))
			{
				if (FocusActor == HitResult.GetActor())
				{
					IInteractable::Execute_HoldInteract(FocusActor,
					                                    HitResult);
				}
				else
				{
					IInteractable::Execute_DragInteract(FocusActor, HitResult);
				}
			}
		}
	}
}

FHitResult UInteractionComponent::GetHitResultByTraceChannel()
{
	if (OwnedCameraComponent)
	{
		if (UWorld* World = GetWorld())
		{
			const FVector CameraLocation = OwnedCameraComponent->GetComponentLocation();
			const FVector GoalLocation = OwnedCameraComponent->GetForwardVector() * InteractionDistance +
				CameraLocation;

			FHitResult HitResult;

			GetWorld()->LineTraceSingleByChannel(HitResult, CameraLocation, GoalLocation, ECC_Camera);

			if (HitResult.bBlockingHit)
			{
				AActor* BlockActor = HitResult.GetActor();

				return HitResult;
			}
		}
	}
	return FHitResult();
}
