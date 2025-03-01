#include "Campus/MiniGames/Alpinist/AlpinistViewComponent.h"

#include "AlpinistGame.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "AlpinistMapEntity.h"
#include "Components/SceneComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Campus/Libraries/MiniGames/Alpinist/AlpinistGameHelper.h"

UAlpinistViewComponent::UAlpinistViewComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	InnerPlayersNiagaraComponent = nullptr;
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

	if (bShouldPlay)
	{
		if (CurrentSnapshot == CoordinateHistory.Num() - 1 || CoordinateHistory.Num() - 1 == -1)
		{
			bShouldPlay = false;

			if (AAlpinistGame* AlpinistGame = Cast<AAlpinistGame>(GetOwner()))
			{
				AlpinistGame->SetFlagVisible(true);
			}
			
			return;
		}

		const TPair<int32, int32> CurrentCoordinate = CoordinateHistory[CurrentSnapshot].Value;
		// UE_LOG(LogTemp, Warning, TEXT("%i, %i"), CurrentCoordinate.Key, CurrentCoordinate.Value);
		const TPair<int32, int32> NextCoordinate = CoordinateHistory[CurrentSnapshot + 1].Value;
		// UE_LOG(LogTemp, Warning, TEXT("%i, %i"), NextCoordinate.Key, NextCoordinate.Value);

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
			}
		}
	}
}

bool UAlpinistViewComponent::InitializeLevel(const TArray<FString>& Map, const USceneComponent* MapViewSceneComponent, UNiagaraComponent* PlayersNiagaraComponent)
{
	UAlpinistGameHelper::bInitializeViewMapProcess = true;
	
	ToStartPosition(nullptr);

	if (!MapViewSceneComponent || !PlayersNiagaraComponent) return false;

	AlpinistMapEntities.Empty();
	if (GetWorld() && AlpinistMapEntityClass->IsValidLowLevel())
	{
		AnchorLocation = MapViewSceneComponent->GetComponentLocation();
		AnchorY = MapViewSceneComponent->GetComponentLocation().Y;
		// UE_LOG(LogTemp, Warning, TEXT("X: %f, Y: %f, Z: %f"), AnchorLocation.X, AnchorLocation.Y, AnchorLocation.Z);

		SpawnLineIndex = 0;
		constexpr float InitialDelay = 0.1f;
		constexpr float BatchInterval = 0.1f;
		FTimerDelegate SpawnLineDelegate;
		SpawnLineDelegate.BindUFunction(this, FName("SpawnLine"), Map, PlayersNiagaraComponent);
		GetWorld()->GetTimerManager().SetTimer(SpawnLineTimerHandle, SpawnLineDelegate, BatchInterval, true, InitialDelay);

		return true;
	}

	return false;
}

bool UAlpinistViewComponent::InitializeWeather(UNiagaraComponent* WeatherNiagaraComponent)
{
	if (WeatherNiagaraComponent && bShouldInitializeWeather)
	{
		WeatherNiagaraComponent->Activate(true);
		bShouldInitializeWeather = false;
		
		return true;
	}

	return false;
}

bool UAlpinistViewComponent::DestroyLevel(const USceneComponent* SceneComponentAround, UNiagaraComponent* PlayersNiagaraComponent)
{
	if (AAlpinistGame* AlpinistGame = Cast<AAlpinistGame>(GetOwner()))
	{
		AlpinistGame->SetFlagVisible(false);
	}
	
	bShouldPlay = false;
	CurrentSnapshot = 0;
	CoordinateHistory = TArray<TPair<int32, TPair<int32, int32>>>();

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

bool UAlpinistViewComponent::DestroyWeather(UNiagaraComponent* WeatherNiagaraComponent)
{
	bShouldInitializeWeather = true;
	
	if (WeatherNiagaraComponent && WeatherNiagaraComponent->GetAsset())
	{
		WeatherNiagaraComponent->Deactivate();
		WeatherNiagaraComponent->DestroyInstance();
		
		return true;
	}

	return false;
}

void UAlpinistViewComponent::StartPlayByHistory(const TArray<TPair<int32, TPair<int32, int32>>>& InCoordinateHistory)
{
	CoordinateHistory = InCoordinateHistory;
	CurrentSnapshot = 0;
	bShouldPlay = true;
	CurrentLocation = PlayerPosition;

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
	UE_LOG(LogTemp, Warning, TEXT("%i, %i"), AlpinistMapEntities.Num(), AlpinistMapEntities[0].Num());
}

void UAlpinistViewComponent::ToStartPosition(UNiagaraComponent* PlayersNiagaraComponent)
{
	bShouldPlay = false;
	CurrentSnapshot = 0;
	CoordinateHistory = TArray<TPair<int32, TPair<int32, int32>>>();

	if (PlayersNiagaraComponent)
	{
		PlayersNiagaraComponent->SetVariablePosition("PlayerPosition", PlayerPosition);
	}
}

void UAlpinistViewComponent::SpawnLine(const TArray<FString>& Map, UNiagaraComponent* PlayersNiagaraComponent)
{
	TArray<AAlpinistMapEntity*> LineEntities = TArray<AAlpinistMapEntity*>();

	AnchorLocation = FVector(AnchorLocation.X, AnchorY, AnchorLocation.Z);
	for (const TCHAR& EntityType : Map[SpawnLineIndex++])
	{
		if (EntityType != 'w')
		{
			if (AAlpinistMapEntity* Entity = GetWorld()->SpawnActor<AAlpinistMapEntity>(AlpinistMapEntityClass, AnchorLocation, FRotator(0.f)))
			{
				Entity->CreateEntity(SnowMeshComponents, AnchorLocation, Density);
				Entity->SetMarkLocation(AnchorLocation + FVector(5.f, Density * 0.4f, Density * 0.3f));
				LineEntities.Add(Entity);

				if (EntityType == 'f' && PlayersNiagaraComponent && PlayersNiagaraComponent->GetAsset())
				{
					PlayersNiagaraComponent->SetVariablePosition("FinishPosition", Entity->GetMarkLocation());

					if (AAlpinistGame* AlpinistGame = Cast<AAlpinistGame>(GetOwner()))
					{
						AlpinistGame->SetFlagLocation(AnchorLocation + FVector(5.f, Density * 0.4f, Density * 0.3f));

						if (AlpinistGame->IsCurrentLevelPassed())
						{
							AlpinistGame->SetFlagVisible(true);
						}
						else
						{
							AlpinistGame->SetFlagVisible(false);
						}
					}
				}
				if (EntityType == 'p' && PlayersNiagaraComponent && PlayersNiagaraComponent->GetAsset())
				{
					InnerPlayersNiagaraComponent = PlayersNiagaraComponent;
					PlayerPosition = Entity->GetMarkLocation();
					PlayersNiagaraComponent->SetVariablePosition("PlayerPosition", PlayerPosition);
					PlayersNiagaraComponent->Activate(true);

					CurrentLocation = PlayerPosition;
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

	if (SpawnLineIndex == Map.Num())
	{
		GetWorld()->GetTimerManager().ClearTimer(SpawnLineTimerHandle);
		UAlpinistGameHelper::bInitializeViewMapProcess = false;
		OnMapOpen.Broadcast(true);
	}
}

