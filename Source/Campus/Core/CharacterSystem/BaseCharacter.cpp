// Fill out your copyright notice in the Description page of Project Settings.
#define BASE_CHARACTER_DEBUG false

#include "BaseCharacter.h"

#include "Camera/CameraComponent.h"
#include "Campus/Chat/ChatManager.h"
#include "Campus/Chat/ChatUserComponent.h"
#include "Components/WidgetInteractionComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "LocalComponents/InteractionComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseCharacter, Log, Log)

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>("InteractionComponent");
	WidgetInteractionComponent = CreateDefaultSubobject<UWidgetInteractionComponent>("WidgetInteractionComponent");

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");

	CameraComponent->SetupAttachment(SpringArmComponent);
	WidgetInteractionComponent->SetupAttachment(CameraComponent);
	SpringArmComponent->SetupAttachment(RootComponent);
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
#ifdef BASE_CHARACTER_DEBUG
	UE_CLOG(WidgetInteractionComponent == nullptr, LogBaseCharacter, Error, TEXT("Widget interaction component is not valid"));
#endif

#ifdef BASE_CHARACTER_DEBUG
	UE_CLOG(InteractionComponent == nullptr, LogBaseCharacter, Error, TEXT("Interaction component is not valid"));
#endif
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Interaction", IE_Pressed, this, &ABaseCharacter::Interact);
	PlayerInputComponent->BindAction("Interaction", IE_Released, this, &ABaseCharacter::EndInteract);

	PlayerInputComponent->BindAxis("ForwardAxis", this, &ABaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("RightAxis", this, &ABaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis("MouseX", this, &ABaseCharacter::LookRight);
	PlayerInputComponent->BindAxis("MouseY", this, &ABaseCharacter::LookUp);
}

void ABaseCharacter::Interact()
{
#ifdef BASE_CHARACTER_DEBUG
	UE_LOG(LogBaseCharacter, Log, TEXT("Interact"))
#endif

#ifdef BASE_CHARACTER_DEBUG
	UE_LOG(LogBaseCharacter, Log, TEXT("Try interact"))
#endif

	InteractionComponent->TryInteract();

#ifdef BASE_CHARACTER_DEBUG
	UE_LOG(LogBaseCharacter, Log, TEXT("Set hold status true"))
#endif

	InteractionComponent->SetHoldStatus(true);
}

void ABaseCharacter::EndInteract()
{
#ifdef BASE_CHARACTER_DEBUG
	UE_LOG(LogBaseCharacter, Log, TEXT("End interact"))
	UE_LOG(LogBaseCharacter, Log, TEXT("Set hold status false"))
#endif
	InteractionComponent->SetHoldStatus(false);
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
