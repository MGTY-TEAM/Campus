
#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "AlpinistViewComponent.generated.h"

class USceneComponent;
class UNiagaraComponent;
class AAlpinistMapEntity;
class UInstancedStaticMeshComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CAMPUS_API UAlpinistViewComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	UAlpinistViewComponent();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	USceneComponent* MapViewSceneComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UNiagaraComponent* PlayersNiagaraComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Classes")
	TSubclassOf<AAlpinistMapEntity> AlpinistMapEntityClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MapParams")
	int32 Density = 8.f;
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool InitializeLevel(const TArray<FString>& Map);
	bool DestroyLevel();
	void StartPlayByHistory(const TArray<TPair<int32, TPair<int32, int32>>>& InCoordinateHistory);
private:
	TArray<TArray<AAlpinistMapEntity*>> AlpinistMapEntities;
	TArray<UInstancedStaticMeshComponent*> MountainMeshComponents;
	TArray<UInstancedStaticMeshComponent*> SnowMeshComponents;

	TArray<TPair<int32, TPair<int32, int32>>> CoordinateHistory;
	bool bShouldPlay = false;
};
