// Fill out your copyright notice in the Description page of Project Settings.


#include "Campus/Pickups/BasePickupableActor.h"
#include "Engine/Engine.h"

ABasePickupableActor::ABasePickupableActor()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ABasePickupableActor::TakingItem(USceneComponent* SceneComponent)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, "Take");
	TakenItem = SceneComponent;
	ItemIsMoving = true;
}

void ABasePickupableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABasePickupableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ItemIsMoving)
	{
		FVector Diraction = TakenItem->GetComponentLocation() - GetActorLocation();
		AddActorWorldOffset(Diraction * Velocity * DeltaTime, false);
		if (Diraction.IsNearlyZero(10.0f))
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "Snap");
			ItemIsMoving = false;
			FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, false);
			AttachToComponent(TakenItem, AttachmentRules);
		}
	}
}

