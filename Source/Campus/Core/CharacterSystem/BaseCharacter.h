// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class UWidgetInteractionComponent;
class USpringArmComponent;
class UChatUserComponent;
class UCameraComponent;
class UInteractionComponent;

UCLASS()
class CAMPUS_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseCharacter();
	
protected:
	virtual void BeginPlay() override;
	
	virtual void Interact();
	virtual void EndInteract();
	
	virtual void MoveForward(float value);
	virtual void MoveRight(float value);
	virtual void LookUp(float value);
	virtual void LookRight(float value);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Components")
	UWidgetInteractionComponent* WidgetInteractionComponent;
	
	UPROPERTY(EditDefaultsOnly, Category="Components")
	UInteractionComponent* InteractionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USpringArmComponent* SpringArmComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera")
	UCameraComponent* CameraComponent;
	
	UPROPERTY(EditAnywhere,  BlueprintReadWrite ,Category="Mouse Settings")
	float MouseSens = 0.4f;
	
public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
};
