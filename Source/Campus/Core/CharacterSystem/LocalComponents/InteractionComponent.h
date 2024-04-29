// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#define INTERACTION_COMPONENT_DEBUG false

DECLARE_LOG_CATEGORY_CLASS(LogInteractionComponent, Log, Log);

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInventoryItemPickup, AInventoryActor*, InventoryActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDialogInteract, AActor*, DialogInterace);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSimpleInteract);

UENUM(BlueprintType)
enum EInteractionState : uint8
{
	EIS_FREE = 0 UMETA(DisplayName = "Free"),
	EIS_DRAG = 1 UMETA(DisplayName = "Drag"),
    EIS_HOLD = 2 UMETA(DisplayName = "Hold")
};

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
	
	UPROPERTY(EditInstanceOnly, Category = "Interaction Component Settings")
	
	bool bInteractHold = false;
	
	FHitResult GetHitResultByTraceChannel();
	
	EInteractionState InteractionState;
	
public:
	UInteractionComponent();
	
	UPROPERTY(BlueprintAssignable)
	FOnInventoryItemPickup OnInventoryItemPickup;
	
	UPROPERTY(BlueprintAssignable)
	FOnDialogInteract OnDialogInteract;
	
	UPROPERTY(BlueprintAssignable)
	FOnSimpleInteract OnSimpleInteract;
	
	void TryInteract();
	void TryEndInteract();

	bool TryPlaceActorOnHitLocation(AInventoryActor* ToPlaceActor);
	bool CanPlaceActorOnHitLocation();
	UFUNCTION()
	void SetHoldStatus(bool bStatus);

	bool bLookAtInteractionComponent = false;
protected:
	virtual void BeginPlay() override;
	void InteractionVisualProcess(AActor* InteractableActor);
	void ChangeInteractableActorViewState(AActor* InteractableActor, bool State);

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};