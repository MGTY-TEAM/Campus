// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryActor.h"

#include "ComponentUtils.h"
#include "PickupSocketComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "GameFramework/SpringArmComponent.h"

AInventoryActor::AInventoryActor()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));

	SetRootComponent(SceneComponent);

	StaticMeshComponent->SetupAttachment(RootComponent);

	CurrentSocket = nullptr;
}

void AInventoryActor::BeginPlay()
{
	Super::BeginPlay();
}

void AInventoryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AInventoryActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

UTexture2D* AInventoryActor::GetRenderTargetTexture() const
{
	if (ItemImageTexture)
	{
		return ItemImageTexture;
	}
	return nullptr;
}

void AInventoryActor::PickupProcess()
{
	SetEnabled(true);
	
	if (CurrentSocket)
	{
		CurrentSocket->RemovePickup();
	}
	DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
}

void AInventoryActor::DropProcess()
{
	SetEnabled(true);
	
	CurrentSocket = nullptr;
	DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
}

void AInventoryActor::SetAttachSocket(UPickupSocketComponent* socket)
{
	CurrentSocket = socket;
}

//POOL FUNCTIONS
void AInventoryActor::SetEnabled(bool bEnabled)
{
	M_IsEnabled = bEnabled;
	if (bEnabled)
	{
		SetActorHiddenInGame(false);
		SetActorTickEnabled(false);
		
	}
	else
	{
		SetActorHiddenInGame(true);
		SetActorTickEnabled(true);
	}
}

bool AInventoryActor::IsEnabled() const
{
	return M_IsEnabled;
}
