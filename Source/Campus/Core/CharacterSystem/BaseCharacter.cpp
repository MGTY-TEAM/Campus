// Fill out your copyright notice in the Description page of Project Settings.
#define BASE_CHARACTER_DEBUG false

#include "BaseCharacter.h"

#include "Engine/LocalPlayer.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "Campus/Chat/ChatManager.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Campus/Chat/Components/ChatUserComponent.h"
#include "Components/WidgetInteractionComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "LocalComponents/InteractionComponent.h"
#include "Campus/Inventory/InventoryActor.h"
#include "LocalComponents/InventoryComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseCharacter, Log, Log)

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>("InteractionComponent");
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>("InventoryComponent");
	WidgetInteractionComponent = CreateDefaultSubobject<UWidgetInteractionComponent>("WidgetInteractionComponent");

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	InventoryActorSlotComponent = CreateDefaultSubobject<USceneComponent>("InventorySlotComponent");

	CameraComponent->SetupAttachment(SpringArmComponent);
	WidgetInteractionComponent->SetupAttachment(CameraComponent);
	SpringArmComponent->SetupAttachment(RootComponent);
	InventoryActorSlotComponent->SetupAttachment(CameraComponent);
}

void ABaseCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	InteractionComponent->OnInventoryItemPickup.AddDynamic(this, &ABaseCharacter::OnPickupInventoryActor);
	
	InventoryComponent->OnSelectedItemChanged.AddUObject(this, &ABaseCharacter::OnSelectedInventoryActorChanged);

	if (IsValid(InventoryWidgetClass))
	{
		if (UUInventoryWidget* InventoryWidget = CreateWidget<UUInventoryWidget>(GetWorld(), InventoryWidgetClass))
		{
			InventoryComponent->ConnectInventoryWidget(InventoryWidget);

			InventoryWidget->AddToViewport();
		}
	}
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	SetupInitialMouseSense();
	
#ifdef BASE_CHARACTER_DEBUG
	UE_CLOG(WidgetInteractionComponent == nullptr, LogBaseCharacter, Error, TEXT("Widget interaction component is not valid"));
#endif

#ifdef BASE_CHARACTER_DEBUG
	UE_CLOG(InteractionComponent == nullptr, LogBaseCharacter, Error, TEXT("Interaction component is not valid"));
#endif
}

void ABaseCharacter::OnSelectedInventoryActorChanged(AInventoryActor* SelectedInventoryActor)
{
	if (SelectedInventoryActor)
	{
#ifdef BASE_CHARACTER_DEBUG
		UE_LOG(LogBaseCharacter, Log, TEXT("Selected inventory actor: %s"), *SelectedInventoryActor->GetName());
#endif
	}
}

void ABaseCharacter::OnPickupInventoryActor(AInventoryActor* InventoryActor)
{
	if (InventoryActor)
	{
		if (InventoryComponent && InventoryActorSlotComponent)
		{
			InventoryActor->PickupProcess();
			InventoryActor->AttachToComponent(InventoryActorSlotComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			
			InventoryComponent->AddItemAndSelect(InventoryActor);
		}
	}
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Interaction
		EnhancedInputComponent->BindAction(InteractionAction, ETriggerEvent::Started, this, &ABaseCharacter::Interact);
		EnhancedInputComponent->BindAction(InteractionAction, ETriggerEvent::Completed, this, &ABaseCharacter::EndInteract);

		// Dropping
		EnhancedInputComponent->BindAction(DropAction, ETriggerEvent::Started, this, &ABaseCharacter::Drop);
		
		// Selection
		EnhancedInputComponent->BindAction(SelectNextAction, ETriggerEvent::Started, this, &ABaseCharacter::SelectNextItem);
		EnhancedInputComponent->BindAction(SelectPrevAction, ETriggerEvent::Started, this, &ABaseCharacter::SelectPrevItem);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABaseCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABaseCharacter::Look);
	}
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

	InteractionComponent->TryEndInteract();
	InteractionComponent->SetHoldStatus(false);
}

void ABaseCharacter::Drop()
{
	if (InventoryComponent)
	{
		if (InteractionComponent->CanPlaceActorOnHitLocation())
		{
			if (AInventoryActor* RemovedActor = InventoryComponent->RemoveSelectedItem())
			{
				InteractionComponent->TryPlaceActorOnHitLocation(RemovedActor);
			}
		}
	}
}

void ABaseCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ABaseCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();
	
	if (Controller)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ABaseCharacter::SelectNextItem()
{
	if (InventoryComponent)
	{
		InventoryComponent->SelectNextItem();
	}
}

void ABaseCharacter::SelectPrevItem()
{
	if (InventoryComponent)
	{
		InventoryComponent->SelectPrevItem();
	}
}

void ABaseCharacter::SetupInitialMouseSense() const
{
	if (LookAction)
	{
		for (auto Modifier : LookAction->Modifiers)
		{
			if (UInputModifier* InputModifier = Modifier.Get())
			{
				if (UInputModifierFOVScaling* FOVInputModifier = Cast<UInputModifierFOVScaling>(InputModifier))
				{
					FOVInputModifier->FOVScale = MouseSens;
				}
			}
		}
	}
}
