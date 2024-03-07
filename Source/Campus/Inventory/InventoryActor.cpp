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

	SceneCaptureComponent->bCaptureEveryFrame = true;
	
}

void AInventoryActor::BeginPlay()
{
	Super::BeginPlay();
}

void AInventoryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (RenderTargetTexture == nullptr) {
		RenderTargetTexture = NewObject<UTextureRenderTarget2D>();
		RenderTargetTexture->InitCustomFormat(512, 512, PF_B8G8R8A8, false);
		RenderTargetTexture->UpdateResourceImmediate();
	}
	
	SceneCaptureComponent->TextureTarget = RenderTargetTexture;

}

void AInventoryActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

UTexture2D* AInventoryActor::GetRenderTargetTexture() const
{
	if (SceneCaptureComponent)
	{
#if INVENTORY_ACTOR_DEBUG
		UE_LOG(LogInventoryActor, Warning, TEXT("Capturig scene"))
#endif

		
		SceneCaptureComponent->CaptureScene();
		
		if (RenderTargetTexture)
		{
#if INVENTORY_ACTOR_DEBUG
			UE_LOG(LogInventoryActor, Warning, TEXT("Render target is valid"))
#endif
			// Creates Texture2D to store TextureRenderTarget content
			UTexture2D *Texture = UTexture2D::CreateTransient(RenderTargetTexture->SizeX, RenderTargetTexture->SizeY, PF_B8G8R8A8);
#if WITH_EDITORONLY_DATA
			Texture->MipGenSettings = TMGS_NoMipmaps;
#endif
			Texture->SRGB = RenderTargetTexture->SRGB;
     
			// Read the pixels from the RenderTarget and store them in a FColor array
			TArray<FColor> SurfData;
			FRenderTarget* RenderTarget = RenderTargetTexture->GameThread_GetRenderTargetResource();
			RenderTarget->ReadPixels(SurfData);
     
			// Lock and copies the data between the textures
			void* TextureData = Texture->GetPlatformData()->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
			const int32 TextureDataSize = SurfData.Num() * 4;
			FMemory::Memcpy(TextureData, SurfData.GetData(), TextureDataSize);
			Texture->GetPlatformData()->Mips[0].BulkData.Unlock();
			// Apply Texture changes to GPU memory
			Texture->UpdateResource();
			
#if INVENTORY_ACTOR_DEBUG
			UE_LOG(LogInventoryActor, Warning, TEXT("Make texture2d"))
#endif
			return Texture;
		}
	}

	return nullptr;

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


