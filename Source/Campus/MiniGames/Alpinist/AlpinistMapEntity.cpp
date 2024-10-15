
#include "Campus/MiniGames/Alpinist/AlpinistMapEntity.h"

#include "Components/InstancedStaticMeshComponent.h"

AAlpinistMapEntity::AAlpinistMapEntity()
{
	PrimaryActorTick.bCanEverTick = false;

}

void AAlpinistMapEntity::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAlpinistMapEntity::CreateEntity(const TArray<UInstancedStaticMeshComponent*>& InstancedStaticMeshes, const FVector& Anchor, const int32 Density)
{
	if (InstancedStaticMeshes.Num() != 2) return;
	
	// UE_LOG(LogTemp, Warning, TEXT("X: %f, Y: %f, Z: %f"), Anchor.X, Anchor.Y, Anchor.Z);

	float Extrusion = 1.f / Density;
	if (InstancedStaticMeshes[0] && InstancedStaticMeshes[1])
	{
		float Height = 0.f;
		for (size_t i = 0; i < Density; ++i)
		{
			Height = Anchor.Z;
			Extrusion = Extrusion + 1.f / Density;
			for (size_t j = 0; j < Density; ++j)
			{
				FTransform InstanceTransform;
				InstanceTransform.SetLocation(FVector(Anchor.X + Extrusion, Anchor.Y + i * 1.f, Height));
				InstanceTransform.SetScale3D(FVector(FMath::RandRange(0.005f, 0.02f), 0.01f, 0.01f));

				const float Value = FMath::RandRange(0.f, 1.f);
				if (Value < 0.92f)
				{
					InstancedStaticMeshes[0]->AddInstance(InstanceTransform, true);
				}
				else
				{
					InstancedStaticMeshes[1]->AddInstance(InstanceTransform, true);
				}
				
				Height = Height + 1.f;
			}
		}
	}
}

