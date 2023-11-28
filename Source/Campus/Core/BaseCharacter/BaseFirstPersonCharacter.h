// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Campus/Interfaces/Interaction/UnPickupableObject.h"
#include "GameFramework/Character.h"
#include "BaseFirstPersonCharacter.generated.h"

class UInventoryItemWidget;
class UInventoryWidget;
class UInventory;
class USpringArmComponent;
class UCameraComponent;
class UBasePickup;

UCLASS()
class CAMPUS_API ABaseFirstPersonCharacter : public ACharacter, public IUnPickupableObject
{
	GENERATED_BODY()

public:
	ABaseFirstPersonCharacter();
	
	UPROPERTY(Category="Movement", EditDefaultsOnly)
	float MouseSpeed;

	UPROPERTY(Category="Interaction", EditDefaultsOnly)
	float InteractionDistance;
	
	UPROPERTY(Category="Interaction", EditDefaultsOnly)
	AActor* FocusActor;

	UBasePickup* PickupClass;

	UPROPERTY(Category="Input", EditDefaultsOnly)
	bool bIsEnableInput = true;

	UPROPERTY(Category="Character", VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArmComponent;
	UPROPERTY(Category="Character", VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;

	FTimerHandle OnFocusTimer;

	bool bIsFirstInteraction = true;
	
protected:
	UInventory* Inventory;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory Class")
	TSubclassOf<UInventoryWidget> InventoryWidgetClass;
	
	virtual void BeginPlay() override;

	virtual void Interact();

	virtual void MoveForward(float value);
	virtual void MoveRight(float value);
	virtual void LookUp(float value);
	virtual void LookRight(float value);

	void FocusOnInteractableActor();

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void UnPickupOn(AActor* Character) override;
	virtual void UnPickupOff() override;
};
