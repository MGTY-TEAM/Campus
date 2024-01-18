// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

#include "Camera/CameraComponent.h"
#include "Campus/Chat/ChatManager.h"
#include "Campus/Chat/ChatUserComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "LocalComponents/InteractionComponent.h"


// Sets default values
ABaseCharacter::ABaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it
	PrimaryActorTick.bCanEverTick = true;
	
	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>("InteractionComponent");
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");

	CameraComponent->SetupAttachment(SpringArmComponent);

	SpringArmComponent->SetupAttachment(RootComponent);
	

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Interaction", IE_Pressed,this, &ABaseCharacter::Interact);

	PlayerInputComponent->BindAxis("ForwardAxis", this, &ABaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("RightAxis", this, &ABaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis("MouseX", this, &ABaseCharacter::LookRight);
	PlayerInputComponent->BindAxis("MouseY", this, &ABaseCharacter::LookUp);
}

void ABaseCharacter::Interact()
{
	InteractionComponent->TryInteract();
}

void ABaseCharacter::MoveForward(float value)
{
	AddMovementInput(GetActorForwardVector() * value);
}

void ABaseCharacter::MoveRight(float value)
{
	AddMovementInput(GetActorRightVector() * value);
}

void ABaseCharacter::LookUp(float value)
{
	AddControllerPitchInput(value * MouseSens * -1);
}

void ABaseCharacter::LookRight(float value)
{
	AddControllerYawInput(value * MouseSens);
}