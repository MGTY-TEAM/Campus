// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryActor.h"

#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "GameFramework/SpringArmComponent.h"

AInventoryActor::AInventoryActor()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	SceneCaptureComponent = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCaptureComponent"));
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));

	SetRootComponent(SceneComponent);
	
	StaticMeshComponent->SetupAttachment(RootComponent);
	
	SpringArmComponent->SetupAttachment(StaticMeshComponent);
	SceneCaptureComponent->SetupAttachment(SpringArmComponent);

	SceneCaptureComponent->TextureTarget = RenderTarget;
}

void AInventoryActor::BeginPlay()
{
	Super::BeginPlay();
}

void AInventoryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

UTexture2D* AInventoryActor::GetRenderTargetTexture() const
{
	UTexture2D* Texture = RenderTarget->ConstructTexture2D(GetWorld(), FString("T_InventoryObjectScreen"),RF_NoFlags);
	
	return Texture;
}
//POOL FUNCTIONS
void AInventoryActor::SetEnabled(bool bEnabled)
{
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


