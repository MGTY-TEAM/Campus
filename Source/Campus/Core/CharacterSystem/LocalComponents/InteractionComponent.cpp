// Fill out your copyright notice in the Description page of Project Settings.



#include "InteractionComponent.h"

#include "Camera/CameraComponent.h"
#include "..\..\..\Interfaces\Interaction\Interactable.h"

DECLARE_LOG_CATEGORY_CLASS(LogInteractionCompoent, Log, Log);

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
		UE_LOG(LogInteractionCompoent, Warning, TEXT("%s"), *HitResult.GetActor()->GetName());
		if (IInteractable* Interactable = Cast<IInteractable>(HitActor))
		{
			UE_LOG(LogInteractionCompoent, Warning, TEXT("Interact  %s"), *HitActor->GetName());
			Interactable->Interact(HitResult.GetComponent(), HitResult.Location, HitResult.Normal);
			OnSimpleInteract.Broadcast();
		}
		if (HitActor->GetClass()->ImplementsInterface(UInteractable::StaticClass()))
		{
			IInteractable::Execute_BPInteract(HitActor, HitResult.GetComponent(), HitResult.Location, HitResult.Normal);
			OnSimpleInteract.Broadcast();
		}
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
		UE_LOG(InteractionComponentLog, Warning, TEXT("Owner"));
		if (UCameraComponent* CameraComponent = Cast<UCameraComponent>(
			GetOwner()->GetComponentByClass(UCameraComponent::StaticClass())))
		{
			UE_LOG(InteractionComponentLog, Warning, TEXT("Camera"));
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
	
	FocusActor = HitResult.GetActor();

	if (FocusActor && bInteractHold)
	{
		if (FocusActor->GetClass()->ImplementsInterface(UInteractable::StaticClass()))
		{
			IInteractable::Execute_BPTickInteract(FocusActor,HitResult.GetComponent(), HitResult.Location, HitResult.Normal);
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
