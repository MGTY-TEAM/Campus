// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Campus/AI/AIDrone/CoreDrone/PlayerInteractionDrone.h"
#include "AIAnimDrone.generated.h"

class UBehaviorTree;

UCLASS()
class CAMPUS_API AAIAnimDrone : public APlayerInteractionDrone
{
	GENERATED_BODY()
	
public:
	AAIAnimDrone();

	UPROPERTY(EditAnywhere, Category = "RobotAnimation")
	float RotationSpeed = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BehaviorTreeAsset;

	UFUNCTION(BlueprintCallable)
	bool DoesHeInteract() const { return InInteraction; }

	UFUNCTION(BlueprintCallable)
	AActor* GetInteractingCharacter() const { return InteractingCharacter; }

	virtual void StartRotateToPlayerAnim();
	virtual void StopRotateToPlayerAnim();
protected:
	virtual void UnPickupOn(AActor* Character) override;
	virtual void UnPickupOff() override;

	FTimerHandle IdleAnimTimer;
	FTimerHandle RotateToPlayerTimer;

private:
	bool InInteraction = false;
	AActor* InteractingCharacter;
};
