// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupSocketComponent.h"

#include "InventoryActor.h"
#include "Engine/StaticMeshSocket.h"


UPickupSocketComponent::UPickupSocketComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	
	PlacedActor = nullptr;
}

void UPickupSocketComponent::OnRegister()
{
	Super::OnRegister();
	
	SetNotifyRigidBodyCollision(true);
}

void UPickupSocketComponent::SetAttachmentScene(USceneComponent* SceneComponent)
{
	AttachmentScene = SceneComponent;
}

bool UPickupSocketComponent::HasPickup()
{
	return PlacedActor != nullptr;
}

AActor* UPickupSocketComponent::GetPickup()
{
	return PlacedActor;
}

bool UPickupSocketComponent::CanPlacePickup(AActor* Actor)
{
	if (PlacedActor)
		return false;

	if (!Actor)
		return false;
	
	for (const auto Class : AvailablePickupClasses)
	{
		if (Actor->IsA(Class))
		{
			return true;
		}
	}
	return false;
}

bool UPickupSocketComponent::PlacePickup(AActor* Actor)
{
	if (CanPlacePickup(Actor))
	{
		PlacedActor = Actor;
		PlacedActor->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
		/*if (AttachmentScene)
		{
			PlacedActor->AttachToComponent(AttachmentScene, FAttachmentTransformRules::SnapToTargetIncludingScale);
		}*/
		PlacedActor->SetActorLocation(GetComponentLocation());
		PlacedActor->AttachToActor(GetOwner(), FAttachmentTransformRules::SnapToTargetIncludingScale);
		/*PlacedActor->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);*/
		return true;
	}
	return false;
}

bool UPickupSocketComponent::RemovePickup(AActor* Actor)
{
	if (PlacedActor)
	{
		PlacedActor->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
		PlacedActor = nullptr;
		return true;
	}
	return false;
}


void UPickupSocketComponent::BeginPlay()
{
	Super::BeginPlay();
}


