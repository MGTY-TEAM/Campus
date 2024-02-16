// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "AIDronePerceptionComponent.generated.h"

UCLASS()
class CAMPUS_API UAIDronePerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()

public:
	AActor* GetInteractionCharacter() const;
	bool CanISee(AActor* Actor);

	void SetLastLocationOf(AActor* Actor);
	FVector GetLastLocationOfInteractionCharacter() { return LastLocationOfInteractionCharacter; }

	bool CheckObstacleInFrontOfTarget(const AActor* Target) const;
	
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sphere", meta =(ClampMin = 0.0f, ClampMax = 1000.0f))
	float RadiusSphere = 100.0f;
private:
	FVector LastLocationOfInteractionCharacter = FVector();
};
