
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AlpinistViewComponent.generated.h"

class USceneComponent;
class UNiagaraComponent;
class AAlpinistMapEntity;
class UInstancedStaticMeshComponent;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnMapOpen, bool);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CAMPUS_API UAlpinistViewComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAlpinistViewComponent();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Classes")
	TSubclassOf<AAlpinistMapEntity> AlpinistMapEntityClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MapParams")
	int32 Density = 8.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MapParams", meta = (ClampMin = "0.1", ClampMax = "100"))
	float MarkMovingSpeed = 5.f;
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool InitializeLevel(const TArray<FString>& Map, const USceneComponent* MapViewSceneComponent, UNiagaraComponent* PlayersNiagaraComponent);
	bool InitializeWeather(UNiagaraComponent* WeatherNiagaraComponent);
	bool DestroyLevel(const USceneComponent* SceneComponentAround, UNiagaraComponent* PlayersNiagaraComponent);
	bool DestroyWeather(UNiagaraComponent* WeatherNiagaraComponent);
	void StartPlayByHistory(const TArray<TPair<int32, TPair<int32, int32>>>& InCoordinateHistory);
	void ToStartPosition(UNiagaraComponent* PlayersNiagaraComponent);

	FOnMapOpen OnMapOpen;
private:
	FVector AnchorLocation;
	float AnchorY = 0.f;
	int32 SpawnLineIndex = 0;
	FTimerHandle SpawnLineTimerHandle;
	UFUNCTION()
	void SpawnLine(const TArray<FString>& Map, UNiagaraComponent* PlayersNiagaraComponent);
	
	TArray<TArray<AAlpinistMapEntity*>> AlpinistMapEntities;
	TArray<UInstancedStaticMeshComponent*> MountainMeshComponents;
	TArray<UInstancedStaticMeshComponent*> SnowMeshComponents;

	TArray<TPair<int32, TPair<int32, int32>>> CoordinateHistory;
	FVector PlayerPosition;
	FVector CurrentLocation;
	UPROPERTY()
	UNiagaraComponent* InnerPlayersNiagaraComponent;
	int32 CurrentSnapshot = 0;
	bool bShouldPlay = false;
	bool bShouldInitializeWeather = true;
	bool bOnEntity = true;
};
