// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Campus/UserInterface/Hud/Inventory/UInventoryWidget.h"

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"


class UInputAction;
class UInputMappingContext;
struct FInputActionValue;
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

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** Interaction Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractionAction;

	/** Drop Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* DropAction;
	
	/** Select Input Actions */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* SelectNextAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* SelectPrevAction;
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

	/** Function to handle moving the character. */
	virtual void Move(const FInputActionValue& Value);

	/** Function to handle looking. */
	virtual void Look(const FInputActionValue& Value);
	
	virtual void SelectNextItem();

	virtual void SelectPrevItem();

	void Drop();
	
	/** Widget interaction component for interacting with UI widgets in the world. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UWidgetInteractionComponent* WidgetInteractionComponent;

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category ="Inventory")
	TSubclassOf<UUInventoryWidget> InventoryWidgetClass;
	
	UFUNCTION()
	void OnSelectedInventoryActorChanged(AInventoryActor* SelectedInventoryActor);

	UFUNCTION()
	void OnPickupInventoryActor(AInventoryActor* InventoryActor);
public:
	/** Called every frame. */
	virtual void Tick(float DeltaTime) override;
	
	/** Function to set up input bindings. */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	/** Component for handling character interactions. */
   	UPROPERTY(EditDefaultsOnly, Category = "Components")
   	UInteractionComponent* InteractionComponent;

private:
	void SetupInitialMouseSense() const;
};

