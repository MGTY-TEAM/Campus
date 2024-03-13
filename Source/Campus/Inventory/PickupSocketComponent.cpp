// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupSocketComponent.h"

#include "InventoryActor.h"
#include "Engine/StaticMeshSocket.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"


UPickupSocketComponent::UPickupSocketComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	
	PlacedActor = nullptr;
}

void UPickupSocketComponent::OnRegister()
{
	Super::OnRegister();
	
	SetNotifyRigidBodyCollision(true);

	SetCollisionProfileName("BlockAll");
}

USceneComponent* UPickupSocketComponent::GetAttachComponent() const
{
	const AActor* Owner = GetOwner();

	TArray<UActorComponent*> Components;
	Owner->GetComponents(Components);

	for (auto Component : Components)
	{
		if (Component->GetName() == AttachComponentName)
		{
			if (USceneComponent* SceneComponent = Cast<USceneComponent>(Component))
			{
				return SceneComponent;
			}
		}
	}
	return nullptr;
}

void UPickupSocketComponent::PlacePickupOnComponent(USceneComponent* Component)
{
	
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

bool UPickupSocketComponent::CanPlacePickup(AInventoryActor* Actor)
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

bool UPickupSocketComponent::PlacePickup(AInventoryActor* Actor)
{
	if (CanPlacePickup(Actor))
	{
		PlacedActor = Actor;
		
		PlacedActor->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
		if (USceneComponent* AttachComponent = GetAttachComponent())
		{
	
			PlacedActor->SetActorLocation(AttachComponent->GetComponentLocation());
			
			PlacedActor->AttachToActor(GetOwner(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			
			PlacedActor->AttachToComponent(AttachComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			PlacedActor->SetAttachSocket(this);
			
			if (OnPickupPlaced.IsBound())
			{
				OnPickupPlaced.Execute(PlacedActor);
			}
			
			return true;
		}
		PlacedActor->SetActorLocation(GetComponentLocation());
		PlacedActor->AttachToActor(GetOwner(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		PlacedActor->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

		PlacedActor->SetAttachSocket(this);

		if (OnPickupPlaced.IsBound())
		{
			OnPickupPlaced.Execute(PlacedActor);
		}

		return true;
		
	}
	return false;
}

bool UPickupSocketComponent::RemovePickup()
{
	if (PlacedActor)
	{
		PlacedActor->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
		PlacedActor = nullptr;

		if (OnPickupRemoved.IsBound())
		{
			OnPickupRemoved.Execute();
		}
		return true;
	}
	return false;
}


void UPickupSocketComponent::BeginPlay()
{
	Super::BeginPlay();
}


