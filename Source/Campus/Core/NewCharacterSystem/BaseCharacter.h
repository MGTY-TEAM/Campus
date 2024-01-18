// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class USpringArmComponent;
class UChatUserComponent;
class UCameraComponent;
class UInteractionComponent;

UCLASS()
class CAMPUS_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void Interact();

	virtual void MoveForward(float value);
	virtual void MoveRight(float value);
	virtual void LookUp(float value);
	virtual void LookRight(float value);
	
	
	UPROPERTY(EditDefaultsOnly, Category="Components")
	UInteractionComponent* InteractionComponent;

	UPROPERTY(EditDefaultsOnly)
	USpringArmComponent* SpringArmComponent;
	
	UPROPERTY(BlueprintReadWrite, Category="Camera")
	UCameraComponent* CameraComponent;
	
	UPROPERTY(EditDefaultsOnly, Category="Mouse Settings")
	float MouseSens = 0.4f;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
