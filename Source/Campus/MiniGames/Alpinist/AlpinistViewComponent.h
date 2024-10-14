
#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "AlpinistViewComponent.generated.h"

class USceneComponent;
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MapParams")
	int32 Density = 8.f;
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool InitializeLevel(const TArray<FString>& Map);
	bool DestroyLevel();
private:
	TArray<AAlpinistMapEntity*> AlpinistMapEntities;
	TArray<UInstancedStaticMeshComponent*> MountainMeshComponents;
	TArray<UInstancedStaticMeshComponent*> SnowMeshComponents;
};
