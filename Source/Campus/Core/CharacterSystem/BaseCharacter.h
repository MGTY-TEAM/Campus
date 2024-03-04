// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class AInventoryActor;
class UInventoryComponent;
class UWidgetInteractionComponent;
class USpringArmComponent;
class UChatUserComponent;
class UCameraComponent;
class UInteractionComponent;

/**
 * Base class for all characters in the game.
 */
UCLASS()
class CAMPUS_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	/** Default constructor. */
	ABaseCharacter();

protected:

	virtual void PostInitializeComponents() override;
	/** Called when the game starts or when spawned. */
	virtual void BeginPlay() override;

	/** Function to handle character interaction. */
	virtual void Interact();

	/** Function to handle ending interaction. */
	virtual void EndInteract();

	/** Function to handle moving the character forward. */
	virtual void MoveForward(float value);

	/** Function to handle moving the character right. */
	virtual void MoveRight(float value);

	/** Function to handle looking up. */
	virtual void LookUp(float value);

	/** Function to handle looking right. */
	virtual void LookRight(float value);
	
	virtual void SelectNextItem();

	virtual void SelectPrevItem();
	
	/** Widget interaction component for interacting with UI widgets in the world. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UWidgetInteractionComponent* WidgetInteractionComponent;

	/** Component for handling character interactions. */
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UInteractionComponent* InteractionComponent;

	/** Component for handling character inventory. */
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UInventoryComponent* InventoryComponent;

	/** Spring arm component for the character's camera. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USpringArmComponent* SpringArmComponent;

	/** Camera component for the character's view. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	UCameraComponent* CameraComponent;

	/** Mouse sensitivity for camera movement. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mouse Settings")
	float MouseSens = 0.4f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inventory")
	USceneComponent* InventoryActorSlotComponent;
	UFUNCTION()
	void OnSelectedInventoryActorChanged(AInventoryActor* SelectedInventoryActor);

	UFUNCTION()
	void OnPickupInventoryActor(AInventoryActor* InventoryActor);
public:
	/** Called every frame. */
	virtual void Tick(float DeltaTime) override;


	
	/** Function to set up input bindings. */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};

