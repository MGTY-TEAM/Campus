// Fill out your copyright notice in the Description page of Project Settings.


#include "Campus/Pickups/Garbage/BaseGarbage.h"
#include "Components/SphereComponent.h"

ABaseGarbage::ABaseGarbage()
{
	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	CollisionComponent->InitSphereRadius(15.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SetRootComponent(CollisionComponent);
}

void ABaseGarbage::TakingItem(USceneComponent* SceneComponent)
{
	Super::TakingItem(SceneComponent);
}
