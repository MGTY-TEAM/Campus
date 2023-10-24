// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../AI/AIDrone/DroneGuide.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "BaseFirstPersonCharacter.generated.h"

UCLASS()
class CAMPUS_API ABaseFirstPersonCharacter : public ACharacter
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

	FTimerHandle OnFocusTimer;

	UPROPERTY(Category="Input", EditDefaultsOnly)
	bool bIsEnableInput = true;
	UPROPERTY(Category="RobotInteraction", EditDefaultsOnly)
	bool bIsRobotInteracts = false;

	UPROPERTY(Category="Character", VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArmComponent;
	UPROPERTY(Category="Character", VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;

	UPROPERTY(EditDefaultsOnly, Category="Drone")
	ADroneGuide* Drone;
	UPROPERTY(EditDefaultsOnly, Category="Drone")
	ATeleportationPlane* PlayerTeleportationPlace;

	
	void AILogicCallBack(const FString& Answer);

protected:
	virtual void BeginPlay() override;
	void AILogicCallBack(FString Answer);

	virtual void Interact();

	virtual void MoveForward(float value);
	virtual void MoveRight(float value);
	virtual void LookUp(float value);
	virtual void LookRight(float value);

	void InteractOnWithRobot();
	void InteractOffWithRobot();
	void FocusOnInteractableActor();


public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION()
	void TeleportToLocation(int index);
	
};
