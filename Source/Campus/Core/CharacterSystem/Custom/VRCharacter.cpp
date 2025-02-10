// Fill out your copyright notice in the Description page of Project Settings.


#include "VRCharacter.h"

#include "Camera/CameraComponent.h"


AVRCharacter::AVRCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	VROriginComponent = CreateDefaultSubobject<USceneComponent>("VRCameraOrigin");

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera Component");


	VROriginComponent->SetupAttachment(RootComponent);

	CameraComponent->SetupAttachment(VROriginComponent);
}

void AVRCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AVRCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AVRCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

