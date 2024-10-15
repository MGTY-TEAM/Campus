
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AlpinistMapEntity.generated.h"

class UInstancedStaticMeshComponent;

UCLASS()
class CAMPUS_API AAlpinistMapEntity : public AActor
{
	GENERATED_BODY()
	
public:	
	AAlpinistMapEntity();

protected:
	virtual void BeginPlay() override;

public:	
	void CreateEntity(const TArray<UInstancedStaticMeshComponent*>& InstancedStaticMeshes, const FVector& Anchor, const int32 Density);
};
