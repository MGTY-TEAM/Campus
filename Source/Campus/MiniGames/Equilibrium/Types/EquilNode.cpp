// Fill out your copyright notice in the Description page of Project Settings.


#include "Campus/MiniGames/Equilibrium/Types/EquilNode.h"
#include "Components/SceneComponent.h"

AEquilNode::AEquilNode()
{
	RotationState = EquilibriumTypes::ENodeRotationState::NRS_Stable;

	PositionLeft = CreateDefaultSubobject<USceneComponent>("PositionLeft");
	PositionLeft->SetupAttachment(GetRootComponent());
	
	PositionRight = CreateDefaultSubobject<USceneComponent>("PositionRight");
	PositionRight->SetupAttachment(GetRootComponent());
	
	StaticMeshComponent->SetupAttachment(GetRootComponent());
}

void AEquilNode::CalculateRotation(FRotator DesiredRotationToSet, FVector DesiredLocationLeftToSet, FVector DesiredLocationRightToSet)
{
	DesiredRotation = DesiredRotationToSet;
	DesiredLocationLeft = DesiredLocationLeftToSet;
	DesiredLocationRight = DesiredLocationRightToSet;
}

void AEquilNode::SetNewState(const EquilibriumTypes::ENodeRotationState& NewRotationState)
{
	RotationState = NewRotationState;
}

void AEquilNode::BeginPlay()
{
	Super::BeginPlay();

	DesiredRotation = StaticMeshComponent->GetRelativeRotation();
	DesiredLocationLeft = GetLeftChild()->GetActorLocation();
	DesiredLocationRight = GetRightChild()->GetActorLocation();
}

void AEquilNode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CalculateRotation(DeltaTime);
}

void AEquilNode::CalculateRotation(float DeltaTime) const
{
	const FRotator InitialRotation = StaticMeshComponent->GetRelativeRotation();
	const FVector InitialLocationLeft = GetLeftChild()->GetActorLocation();
	const FVector InitialLocationRight = GetRightChild()->GetActorLocation();
	
	if (InitialRotation != DesiredRotation)
	{
		const FRotator NewRotation = FMath::RInterpTo(InitialRotation, DesiredRotation, DeltaTime, InterpSpeedTime);
		StaticMeshComponent->SetRelativeRotation(NewRotation);
	}
	
	if (InitialLocationLeft != DesiredLocationLeft && InitialLocationRight != DesiredLocationRight && GetLeftChild() && GetRightChild())
	{
		const FVector NewLocationLeftChild = FMath::VInterpTo(InitialLocationLeft, GetPositionLeft()->GetComponentLocation() + DesiredLocationLeft, DeltaTime, InterpSpeedTime);
		GetLeftChild()->SetActorLocation(NewLocationLeftChild);
		const FVector NewLocationRightChild = FMath::VInterpTo(InitialLocationRight, GetPositionRight()->GetComponentLocation() + DesiredLocationRight, DeltaTime, InterpSpeedTime);
		GetRightChild()->SetActorLocation(NewLocationRightChild);
	}
}

