// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"
class IInteractable;
class IInteractable;
DECLARE_LOG_CATEGORY_CLASS(InteractionComponentLog, Log, Log);


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInventoryItemPickup, AActor*, PickupedActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDialogInteract, AActor*, DialogInterace);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSimpleInteract);


class UCameraComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CAMPUS_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	// Sets default values for this component's properties
	UInteractionComponent();
	
	void TryInteract();
	
	UPROPERTY(EditDefaultsOnly, Category="Interaction Component Settings")
	float InteractionDistance = 300;

	UPROPERTY(BlueprintAssignable)
	FOnInventoryItemPickup OnInventoryItemPickup;
	
	UPROPERTY(BlueprintAssignable)
	FOnDialogInteract OnDialogInteract;
	
	UPROPERTY(BlueprintAssignable)
	FOnSimpleInteract OnSimpleInteract;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

private:
	AActor* FocusActor;

	FHitResult GetHitResultByTraceChannel();

	UPROPERTY(/*EditDefaultsOnly, Category = "Interaction Component Settings"*/)
	UCameraComponent* OwnedCameraComponent;

	
};
