// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractionComponent.h"
#include "Camera/CameraComponent.h"
#include "..\..\..\Interfaces\Interaction\Interactable.h"
#include "Campus/Inventory/InventoryActor.h"
#include "Campus/Inventory/PickupSocketComponent.h"
#include "Components/WidgetInteractionComponent.h"

UInteractionComponent::UInteractionComponent(): FocusActor(nullptr), OwnedCameraComponent(nullptr)
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UInteractionComponent::TryInteract()
{
	FHitResult HitResult = GetHitResultByTraceChannel();
	if (AActor* HitActor = HitResult.GetActor())
	{
		
#ifdef  INTERACTION_COMPONENT_DEBUG
		UE_LOG(LogInteractionComponent, Log, TEXT("Actor hited: %s"), *HitResult.GetActor()->GetName());
#endif
		
		if (IInteractable* Interactable = Cast<IInteractable>(HitActor))
		{
			
#ifdef INTERACTION_COMPONENT_DEBUG
			UE_LOG(LogInteractionComponent, Log, TEXT("Interact with implemented actor: %s"), *HitActor->GetName());
#endif
			
			Interactable->Interact(HitResult.GetComponent(), HitResult.Location, HitResult.Normal);
			OnSimpleInteract.Broadcast();

			if (AInventoryActor* InventoryActor = Cast<AInventoryActor>(HitActor))
			{
#ifdef INTERACTION_COMPONENT_DEBUG
				UE_LOG(LogInteractionComponent, Log, TEXT("Interact with inventory actor: %s"), *HitActor->GetName());
#endif
				OnInventoryItemPickup.Broadcast(InventoryActor);
			}
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
		
#ifdef INTERACTION_COMPONENT_DEBUG
		UE_LOG(LogInteractionComponent, Log, TEXT("Widget Interaction"));
#endif
		
		WidgetInteractionComponent->PressPointerKey(EKeys::LeftMouseButton);
		WidgetInteractionComponent->ReleasePointerKey(EKeys::LeftMouseButton);
	}
}

bool UInteractionComponent::TryPlaceActorOnHitLocation(AInventoryActor* ToPlaceActor)
{
	if (!ToPlaceActor)
		return false;
	
	FHitResult HitResult = GetHitResultByTraceChannel();
	
	if (HitResult.IsValidBlockingHit())
	{
		if (UPickupSocketComponent* PickupSocketComponent  = Cast<UPickupSocketComponent>(HitResult.GetComponent()))
		{
			UE_LOG(LogInteractionComponent, Warning, TEXT("TryPlaceActorOnHitLocation: PickupSocketComponentDetected"));
			if (PickupSocketComponent->PlacePickup(ToPlaceActor))
			{
				UE_LOG(LogInteractionComponent, Warning, TEXT("TryPlaceActorOnHitLocation: Placed"));
				return true;
			}
		}
		ToPlaceActor->DropProcess();
		ToPlaceActor->SetActorLocation(HitResult.Location);
		return true;
	}
	return false;
}

bool UInteractionComponent::CanPlaceActorOnHitLocation()
{
	FHitResult HitResult = GetHitResultByTraceChannel();
	
	if (HitResult.IsValidBlockingHit())
	{
		if (UPickupSocketComponent* PickupSocketComponent  = Cast<UPickupSocketComponent>(HitResult.GetComponent()))
		{
			if (!PickupSocketComponent->HasPickup())
			{
				return true;
			}
		}
		else
		{
			return true;
		}
	}
	return false;
}


void UInteractionComponent::SetHoldStatus(bool bStatus)
{
	bInteractHold = bStatus;
}

void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
	if (GetOwner())
	{
		
#ifdef INTERACTION_COMPONENT_DEBUG
		UE_LOG(LogInteractionComponent, Warning, TEXT("Owner"));
#endif
		
		if (UCameraComponent* CameraComponent = Cast<UCameraComponent>(
			GetOwner()->GetComponentByClass(UCameraComponent::StaticClass())))
		{
			
#ifdef INTERACTION_COMPONENT_DEBUG
			UE_LOG(LogInteractionComponent, Log, TEXT("Camera"));
#endif
			
			OwnedCameraComponent = CameraComponent;
		}
	}
}

void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	FHitResult HitResult = GetHitResultByTraceChannel();
	
	if (!bInteractHold)
	{
		FocusActor = HitResult.GetActor();
		bLookAtInteractionComponent = true;
	}
	else
	{
		if (FocusActor)
		{
			if (FocusActor->GetClass()->ImplementsInterface(UInteractable::StaticClass()))
			{
				if (FocusActor == HitResult.GetActor())
				{
					IInteractable::Execute_HoldInteract(FocusActor, HitResult);
					
				}
				else
				{
					IInteractable::Execute_DragInteract(FocusActor, HitResult);
				}
			}
		}
		bLookAtInteractionComponent = false;
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

			GetWorld()->LineTraceSingleByChannel(HitResult, CameraLocation, GoalLocation, ECC_Visibility);

			if (HitResult.bBlockingHit)
			{
				return HitResult;
			}
		}
	}
	return FHitResult();
}
