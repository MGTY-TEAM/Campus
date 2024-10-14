
#include "Campus/MiniGames/Alpinist/AlpinistViewComponent.h"

#include "AlpinistGame.h"
#include "AlpinistMapEntity.h"
#include "Components/SceneComponent.h"
#include "Components/InstancedStaticMeshComponent.h"

UAlpinistViewComponent::UAlpinistViewComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	MapViewSceneComponent = CreateDefaultSubobject<USceneComponent>("MapViewSceneComponent");
	MapViewSceneComponent->SetupAttachment(GetAttachmentRoot());
}

void UAlpinistViewComponent::BeginPlay()
{
	Super::BeginPlay();

	if (const AAlpinistGame* AlpinistGame = Cast<AAlpinistGame>(GetOwner()))
	{
		MountainMeshComponents.Add(AlpinistGame->GetMainMountainMeshComponent());
		MountainMeshComponents.Add(AlpinistGame->GetSecondMountainMeshComponent());
		SnowMeshComponents.Add(AlpinistGame->GetMainSnowMeshComponent());
		SnowMeshComponents.Add(AlpinistGame->GetSecondSnowMeshComponent());
	}
}

void UAlpinistViewComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

bool UAlpinistViewComponent::InitializeLevel(const TArray<FString>& Map)
{
	FVector AnchorLocation = MapViewSceneComponent->GetComponentLocation();
	const float AnchorY = MapViewSceneComponent->GetComponentLocation().Y;
	UE_LOG(LogTemp, Warning, TEXT("X: %f, Y: %f, Z: %f"), AnchorLocation.X, AnchorLocation.Y, AnchorLocation.Z);
	for (const FString& Line : Map)
	{
		AnchorLocation = FVector(AnchorLocation.X, AnchorY, AnchorLocation.Z);
		for (const TCHAR& EntityType : Line)
		{
			if (EntityType != 'w')
			{
				if (AAlpinistMapEntity* Entity = NewObject<AAlpinistMapEntity>())
				{
					Entity->CreateEntity(SnowMeshComponents, AnchorLocation, Density);
				}
			}
			else
			{
				if (AAlpinistMapEntity* Entity = NewObject<AAlpinistMapEntity>())
				{
					Entity->CreateEntity(MountainMeshComponents, AnchorLocation, Density);
				}
			}
			
			AnchorLocation = AnchorLocation + FVector(0.f, -Density, 0.f);
		}
		AnchorLocation = AnchorLocation + FVector(2.f, 0.f, -Density);
	}
	
	return false;
}

bool UAlpinistViewComponent::DestroyLevel()
{
	return false;
}

