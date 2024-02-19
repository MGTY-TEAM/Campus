// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#define INTERACTION_COMPONENT_DEBUG false

DECLARE_LOG_CATEGORY_CLASS(LogInteractionComponent, Log, Log);

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInventoryItemPickup, AActor*, PickupedActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDialogInteract, AActor*, DialogInterace);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSimpleInteract);

class IInteractable;
class UCameraComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CAMPUS_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()
	
	AActor* FocusActor;
	
	UCameraComponent* OwnedCameraComponent;

	UPROPERTY(EditDefaultsOnly, Category="Interaction Component Settings")
	float InteractionDistance = 300;
	
	bool bInteractHold = false;
	
	FHitResult GetHitResultByTraceChannel();
	
public:
	UInteractionComponent();
	
	UPROPERTY(BlueprintAssignable)
	FOnInventoryItemPickup OnInventoryItemPickup;
	
	UPROPERTY(BlueprintAssignable)
	FOnDialogInteract OnDialogInteract;
	
	UPROPERTY(BlueprintAssignable)
	FOnSimpleInteract OnSimpleInteract;
	
	void TryInteract();
	
	UFUNCTION()
	void SetHoldStatus(bool bStatus);
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
