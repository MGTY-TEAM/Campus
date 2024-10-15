
#include "Campus/MiniGames/Alpinist/AlpinistViewComponent.h"

#include "AlpinistGame.h"
#include "NiagaraComponent.h"
#include "AlpinistMapEntity.h"
#include "Components/SceneComponent.h"
#include "Components/InstancedStaticMeshComponent.h"

UAlpinistViewComponent::UAlpinistViewComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	MapViewSceneComponent = CreateDefaultSubobject<USceneComponent>("MapViewSceneComponent");
	// MapViewSceneComponent->SetupAttachment(this);

	PlayersNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>("PlayersNiagaraComponent");
	// PlayersNiagaraComponent->SetupAttachment(this);
}

void UAlpinistViewComponent::BeginPlay()
{
	Super::BeginPlay();

	if (PlayersNiagaraComponent && MapViewSceneComponent)
	{
		MapViewSceneComponent->RegisterComponent();
		MapViewSceneComponent->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
		PlayersNiagaraComponent->RegisterComponent();
		PlayersNiagaraComponent->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
	}

	if (const AAlpinistGame* AlpinistGame = Cast<AAlpinistGame>(GetOwner()))
	{
		MountainMeshComponents.Add(AlpinistGame->GetMainMountainMeshComponent());
		MountainMeshComponents.Add(AlpinistGame->GetSecondMountainMeshComponent());
		SnowMeshComponents.Add(AlpinistGame->GetMainSnowMeshComponent());
		SnowMeshComponents.Add(AlpinistGame->GetSecondSnowMeshComponent());
	}

	if (PlayersNiagaraComponent && !PlayersNiagaraComponent->IsPaused())
	{
		PlayersNiagaraComponent->SetActive(false);
		// PlayersNiagaraComponent->Deactivate();
		// PlayersNiagaraComponent->SetPaused(true);
		// PlayersNiagaraComponent->SetVisibility(false);
	}
}

void UAlpinistViewComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

bool UAlpinistViewComponent::InitializeLevel(const TArray<FString>& Map)
{
	AlpinistMapEntities.Empty();
	if (GetWorld() && AlpinistMapEntityClass->IsValidLowLevel())
	{
		FVector AnchorLocation = MapViewSceneComponent->GetComponentLocation();
		const float AnchorY = MapViewSceneComponent->GetComponentLocation().Y;
		// UE_LOG(LogTemp, Warning, TEXT("X: %f, Y: %f, Z: %f"), AnchorLocation.X, AnchorLocation.Y, AnchorLocation.Z);
		for (const FString& Line : Map)
		{
			TArray<AAlpinistMapEntity*> LineEntities = TArray<AAlpinistMapEntity*>();
		
			AnchorLocation = FVector(AnchorLocation.X, AnchorY, AnchorLocation.Z);
			for (const TCHAR& EntityType : Line)
			{
				if (EntityType != 'w')
				{
					if (AAlpinistMapEntity* Entity = GetWorld()->SpawnActor<AAlpinistMapEntity>(AlpinistMapEntityClass, AnchorLocation, FRotator(0.f)))
					{
						Entity->CreateEntity(SnowMeshComponents, AnchorLocation, Density);
						LineEntities.Add(Entity);
					}
				}
				else
				{
					if (AAlpinistMapEntity* Entity = GetWorld()->SpawnActor<AAlpinistMapEntity>(AlpinistMapEntityClass, AnchorLocation, FRotator(0.f)))
					{
						Entity->CreateEntity(MountainMeshComponents, AnchorLocation, Density);
						LineEntities.Add(Entity);

						if (EntityType == 'p' && PlayersNiagaraComponent)
						{
							PlayersNiagaraComponent->SetActive(true);
							PlayersNiagaraComponent->SetVectorParameter("PlayerLocation",  AnchorLocation/*FVector(-835.0f, -501.0f, 104.f)*/);
							
							// PlayersNiagaraComponent->ActivateSystem();
							// PlayersNiagaraComponent->SetVariablePosition("PlayerPosition", AnchorLocation/*FVector(-835.0f, -501.0f, 104.f)*/);
							// PlayersNiagaraComponent->SetPaused(false);
							// PlayersNiagaraComponent->SetVisibility(true);
						}
					}
				}
			
				AnchorLocation = AnchorLocation + FVector(0.f, -Density, 0.f);
			}
			AnchorLocation = AnchorLocation + FVector(1.5f, 0.f, -Density);

			AlpinistMapEntities.Add(LineEntities);
		}
	
		return true;
	}
	
	return false;
}

bool UAlpinistViewComponent::DestroyLevel()
{
	for (UInstancedStaticMeshComponent* InstancedStaticMeshComponent : MountainMeshComponents)
	{
		InstancedStaticMeshComponent->ClearInstances();
	}
	for (UInstancedStaticMeshComponent* InstancedStaticMeshComponent : SnowMeshComponents)
	{
		InstancedStaticMeshComponent->ClearInstances();
	}
	
	for (TArray<AAlpinistMapEntity*>& LineEntity : AlpinistMapEntities)
	{
		for (AAlpinistMapEntity* Entity : LineEntity)
		{
			if (Entity && IsValid(Entity))
			{
				Entity->Destroy();
			}
		}
		LineEntity.RemoveAll([](AAlpinistMapEntity* Entity)
		{
			return Entity == nullptr || !IsValid(Entity);
		});
	}
	AlpinistMapEntities.Empty();

	if (PlayersNiagaraComponent && !PlayersNiagaraComponent->IsPaused())
	{
		// PlayersNiagaraComponent->Deactivate();
		/*PlayersNiagaraComponent->SetPaused(true);
		PlayersNiagaraComponent->SetVisibility(false);*/
	}
	
	return true;
}

void UAlpinistViewComponent::StartPlayByHistory(const TArray<TPair<int32, TPair<int32, int32>>>& InCoordinateHistory)
{
	CoordinateHistory = InCoordinateHistory;
	bShouldPlay = true;

	for (const TPair<int32, TPair<int32, int32>>& Pair : CoordinateHistory)
	{
		FString Direction = FString();

		if (Pair.Key == 4)
		{
			Direction = FString("UP");
		}
		if (Pair.Key == 8)
		{
			Direction = FString("DOWN");
		}
		if (Pair.Key == 1)
		{
			Direction = FString("LEFT");
		}
		if (Pair.Key == 2)
		{
			Direction = FString("RIGHT");
		}
		
		UE_LOG(LogTemp, Warning, TEXT("%s: %i, %i"), *Direction, Pair.Value.Key, Pair.Value.Value);
	}
}
