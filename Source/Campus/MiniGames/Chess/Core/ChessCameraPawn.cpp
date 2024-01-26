// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessCameraPawn.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"


// Sets default values
AChessCameraPawn::AChessCameraPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");

	CameraComponent->SetupAttachment(SpringArmComponent);
	SpringArmComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AChessCameraPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AChessCameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AChessCameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

