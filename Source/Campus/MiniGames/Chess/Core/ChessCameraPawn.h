// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ChessCameraPawn.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class CAMPUS_API AChessCameraPawn : public APawn
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category="Camera")
	UCameraComponent* CameraComponent;


	
public:
	// Sets default values for this pawn's properties
	AChessCameraPawn();
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Camera")
	USpringArmComponent* SpringArmComponent;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
