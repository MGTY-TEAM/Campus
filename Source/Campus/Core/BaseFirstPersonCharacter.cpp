// Fill out your copyright notice in the Description page of Project Settings.


// Include necessary headers and dependencies.
#include "BaseFirstPersonCharacter.h"

#include "DrawDebugHelpers.h"
#include "TimerManager.h"
#include "../AI/AIDrone/DroneGuide.h"
#include "../UserInterface/ChatBox.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Constructor
ABaseFirstPersonCharacter::ABaseFirstPersonCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Initialize SpringArmComponent and CameraComponent, then attach them to the root component.
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	SpringArmComponent->SetupAttachment(RootComponent);
	CameraComponent->SetupAttachment(SpringArmComponent);
}

// BeginPlay function
void ABaseFirstPersonCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Set up timers for robot interaction functions
	
	/*GetWorldTimerManager().SetTimer(OnFocusTimer, this, &ABaseFirstPersonCharacter::FocusOnInteractableActor, 0.01f, true, 0.0f);
	Drone = Cast<ADroneGuide>(UGameplayStatics::GetActorOfClass(GetWorld(), ADroneGuide::StaticClass()));

	
	if (Drone->ChatWidget)
	{
		Drone->ChatWidget->TeleportationEvent.AddDynamic(this, &ABaseFirstPersonCharacter::TeleportToLocation);
	}*/

}

// Function for interaction
void ABaseFirstPersonCharacter::Interact()
{
	// Define start point, direction, and end point for interaction
	FVector Start = CameraComponent->GetComponentLocation();
	FVector ForwardVector = CameraComponent->GetForwardVector();
	FVector End = ((ForwardVector * InteractionDistance) + Start);

	FHitResult OutHit;
	FCollisionQueryParams CollisionParams;

	// Perform a line trace
	if (GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, CollisionParams))
	{
		if (OutHit.bBlockingHit)
		{
			// Check if the object hit by the line trace implements the IInteractable interface
			IInteractable* InteractableObject = Cast<IInteractable>(OutHit.GetActor()); 
			if (InteractableObject)
			{
				// If the object is interactable, interact with it
				FocusActor = OutHit.GetActor();
				InteractableObject->Interact();
				if (Cast<ADroneGuide>(OutHit.GetActor()))
				{
					// If the object is a drone, check whether the character is already interacting with the robot
					if (bIsRobotInteracts)
					{
						InteractOffWithRobot();
						InteractableObject->EndInteract();
					}
					else
					{
						InteractOnWithRobot();
					}
				}
			}
		}
	}

	// Draw a debug line to visualize the line trace
	DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 5, 0, 1);
}

// Function to set up player input
void ABaseFirstPersonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind interaction function to an action mapping
	PlayerInputComponent->BindAction("Interaction", IE_Pressed, this, &ABaseFirstPersonCharacter::Interact);

	// Bind movement and look functions to axis mappings
	PlayerInputComponent->BindAxis("ForwardAxis", this, &ABaseFirstPersonCharacter::MoveForward);
	PlayerInputComponent->BindAxis("RightAxis", this, &ABaseFirstPersonCharacter::MoveRight);
	PlayerInputComponent->BindAxis("MouseX", this, &ABaseFirstPersonCharacter::LookRight);
	PlayerInputComponent->BindAxis("MouseY", this, &ABaseFirstPersonCharacter::LookUp);

	UE_LOG(LogTemp, Warning, TEXT("BindAxis"));
}

void ABaseFirstPersonCharacter::TeleportToLocation(int index)
{
	
	if(Cast<ATeleportationPlane>(Drone->TeleportationPlaces[index]))
	{
		PlayerTeleportationPlace = Cast<ATeleportationPlane>(Drone->TeleportationPlaces[index]);
		SetActorLocation(PlayerTeleportationPlace->PlayerPlane->GetComponentLocation());
	}
	
}

// Movement and look functions
void ABaseFirstPersonCharacter::MoveForward(float value)
{
	// Add movement input in the forward direction
	
	if (bIsEnableInput)
	{
		/*UE_LOG(LogTemp, Warning, TEXT("MoveForward, %f"), value);*/
		AddMovementInput(GetActorForwardVector() * value);
	}
}

void ABaseFirstPersonCharacter::MoveRight(float value)
{
	// Add movement input in the right direction
	if (bIsEnableInput)
	{
		AddMovementInput(GetActorRightVector() * value);
	}
}

void ABaseFirstPersonCharacter::LookUp(float value)
{
	// Add controller pitch input
	if (bIsEnableInput)
	{
		AddControllerPitchInput(value * MouseSpeed * -1);
	}
}

void ABaseFirstPersonCharacter::LookRight(float value)
{
	// Add controller yaw input
	if (bIsEnableInput)
	{
		AddControllerYawInput(value * MouseSpeed);
	}
}

// Robot interaction functions
void ABaseFirstPersonCharacter::InteractOnWithRobot()
{
	// Start interaction with robot
	bIsEnableInput = false;
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;

	CameraComponent->bUsePawnControlRotation = false;
	
	bIsRobotInteracts = true;
}

void ABaseFirstPersonCharacter::InteractOffWithRobot()
{
	// Stop interaction with robot
	bIsEnableInput = true;
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;

	CameraComponent->bUsePawnControlRotation = true;

	bIsRobotInteracts = false;
}

void ABaseFirstPersonCharacter::FocusOnInteractableActor()
{
	// Rotate towards robot
	if (bIsRobotInteracts)
	{
		FVector StartLocation = this->GetCapsuleComponent()->GetComponentLocation();
		FVector TargetLocation = FocusActor->GetActorLocation();

		// Find rotation that looks at target
		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(StartLocation, TargetLocation);

		FRotator StartRotation = this->GetCapsuleComponent()->GetComponentRotation();
		FRotator EndRotation = LookAtRotation;
		float RotationSpeed = 2.f;
	
		// Interpolate between current rotation and target rotation
		FRotator InterpolatedRotation = FMath::RInterpTo(StartRotation, EndRotation, GetWorld()->GetDeltaSeconds(), RotationSpeed);
		GetWorld()->GetFirstPlayerController()->SetControlRotation(InterpolatedRotation);

		// Lerp between current camera pitch and target pitch
		float PitchRotate = FMath::Lerp(CameraComponent->GetComponentRotation().Pitch, 0.0f,GetWorld()->GetDeltaSeconds());

		CameraComponent->SetWorldRotation(FRotator(PitchRotate,InterpolatedRotation.Yaw,InterpolatedRotation.Roll));

		// Check distance to robot
		if (FVector::Dist(this->GetCapsuleComponent()->GetComponentLocation(),FocusActor->GetActorLocation()) < 300)
		{
			// Calculate target location
			FVector DesiredLocation  = this->GetCapsuleComponent()->GetForwardVector() * 300;
			FVector EndLocation = FVector(DesiredLocation.X * -1,DesiredLocation.Y * -1, DesiredLocation.Z) + StartLocation;
			float StepSpeed = 0.5f;
			
			// Interpolate between current location and target location
			FVector InterpolatedVector = FMath::VInterpTo(StartLocation, EndLocation, GetWorld()->GetDeltaSeconds(),StepSpeed);

			SetActorLocation(InterpolatedVector,false);
		}
	}
}

void ABaseFirstPersonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

