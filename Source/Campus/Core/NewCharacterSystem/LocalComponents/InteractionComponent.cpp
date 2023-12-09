// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionComponent.h"

#include "Camera/CameraComponent.h"
#include "Campus/Core/NewCharacterSystem/BaseCharacter.h"
#include "Campus/Interfaces/Interaction/Interactable.h"
#include "..\..\..\Interfaces\Interaction\SubInteractable.h"


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
		if (ISubInteractable* Interactable = Cast<ISubInteractable>(HitActor))
		{
			Interactable->Interact(HitResult.GetComponent(), HitResult.Location, HitResult.Normal);
			OnSimpleInteract.Broadcast();
		}
	}
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

	FocusActor = GetHitResultByTraceChannel().GetActor();
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
