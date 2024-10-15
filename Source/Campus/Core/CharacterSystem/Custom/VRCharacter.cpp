// Fill out your copyright notice in the Description page of Project Settings.


#include "VRCharacter.h"

#include "IHeadMountedDisplay.h"
#include "IXRTrackingSystem.h"
#include "openxr/openxr.h"
#include "openxr/openxr_platform.h"
#include "MotionControllerComponent.h"
#include "Camera/CameraComponent.h"


AVRCharacter::AVRCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	VROriginComponent = CreateDefaultSubobject<USceneComponent>("VRCameraOrigin");

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera Component");

	LeftMotionControllerComponent = CreateDefaultSubobject<UMotionControllerComponent>("Left Motion Controller");
	RightMotionControllerComponent = CreateDefaultSubobject<UMotionControllerComponent>("Right Motion Controller");

	VROriginComponent->SetupAttachment(RootComponent);

	CameraComponent->SetupAttachment(VROriginComponent);

	LeftMotionControllerComponent->MotionSource = FName("Left");
	LeftMotionControllerComponent->SetupAttachment(VROriginComponent);

	RightMotionControllerComponent->MotionSource = FName("Right");
	RightMotionControllerComponent->SetupAttachment(VROriginComponent);

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

