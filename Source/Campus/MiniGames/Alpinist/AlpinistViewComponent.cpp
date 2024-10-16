
#include "Campus/MiniGames/Alpinist/AlpinistViewComponent.h"

#include "AlpinistGame.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "AlpinistMapEntity.h"
#include "Components/SceneComponent.h"
#include "Components/InstancedStaticMeshComponent.h"

UAlpinistViewComponent::UAlpinistViewComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
	InnerPlayersNiagaraComponent = nullptr;
}

void UAlpinistViewComponent::BeginPlay()
{
	Super::BeginPlay();

	OnUpdatePosition.BindUObject(this, &UAlpinistViewComponent::UpdatePosition);
	
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

	if (bShouldPlay)
	{
		const TPair<int32, int32> CurrentCoordinate = CoordinateHistory[CurrentSnapshot].Value;
		const TPair<int32, int32> NextCoordinate = CoordinateHistory[CurrentSnapshot + 1].Value;
		UE_LOG(LogTemp, Warning, TEXT("%i, %i"), CurrentSnapshot, CoordinateHistory.Num());
		const AAlpinistMapEntity* CurrentEntity = AlpinistMapEntities[CurrentCoordinate.Key][CurrentCoordinate.Value];
		const AAlpinistMapEntity* NextEntity = AlpinistMapEntities[NextCoordinate.Key][NextCoordinate.Value];
		
		if (CurrentEntity && NextEntity && InnerPlayersNiagaraComponent)
		{
			if (bOnEntity)
			{
				CurrentLocation = CurrentEntity->GetMarkLocation();
				bOnEntity = false;
			}
			
			const FVector NextLocation = NextEntity->GetMarkLocation();
			CurrentLocation = FMath::VInterpConstantTo(CurrentLocation, NextLocation, DeltaTime, MarkMovingSpeed);

			InnerPlayersNiagaraComponent->SetVariablePosition("PlayerPosition", CurrentLocation);
			// UE_LOG(LogTemp, Warning, TEXT("%f, %f, %f"), CurrentLocation.X, CurrentLocation.Y, CurrentLocation.Z);
			
			if (FVector::Dist(CurrentLocation, NextLocation) < KINDA_SMALL_NUMBER)
			{
				++CurrentSnapshot;
				bOnEntity = true;

				if (CurrentSnapshot == CoordinateHistory.Num() - 1)
				{
					bShouldPlay = false;
				}
			}
		}
	}
}

bool UAlpinistViewComponent::InitializeLevel(const TArray<FString>& Map, const USceneComponent* MapViewSceneComponent, UNiagaraComponent* PlayersNiagaraComponent)
{
	if (!MapViewSceneComponent || !PlayersNiagaraComponent) return false;
	
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
						Entity->SetMarkLocation(AnchorLocation + FVector(5.f, Density * 0.4f, Density * 0.3f));
						LineEntities.Add(Entity);

						if (EntityType == 'p' && PlayersNiagaraComponent && PlayersNiagaraComponent->GetAsset())
						{
							InnerPlayersNiagaraComponent = PlayersNiagaraComponent;
							PlayersNiagaraComponent->SetVariablePosition("PlayerPosition", Entity->GetMarkLocation());
							PlayersNiagaraComponent->Activate(true);
						}
					}
				}
				else
				{
					if (AAlpinistMapEntity* Entity = GetWorld()->SpawnActor<AAlpinistMapEntity>(AlpinistMapEntityClass, AnchorLocation, FRotator(0.f)))
					{
						Entity->CreateEntity(MountainMeshComponents, AnchorLocation, Density);
						LineEntities.Add(Entity);
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

bool UAlpinistViewComponent::DestroyLevel(const USceneComponent* SceneComponentAround, UNiagaraComponent* PlayersNiagaraComponent)
{
	bShouldPlay = false;
	
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

	if (PlayersNiagaraComponent && PlayersNiagaraComponent->GetAsset())
	{
		PlayersNiagaraComponent->Deactivate();
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

void UAlpinistViewComponent::UpdatePosition(FVector NewPosition)
{
	if (InnerPlayersNiagaraComponent)
	{
		InnerPlayersNiagaraComponent->SetVariablePosition("PlayerPosition", NewPosition);
	}
}
