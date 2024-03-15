// Fill out your copyright notice in the Description page of Project Settings.


#include "Campus/MiniGames/Equilibrium/Types/EquilNode.h"
#include "Components/SceneComponent.h"

AEquilNode::AEquilNode()
{
	RotationState = EquilibriumTypes::ENodeRotationState::NRS_Stable;

	PositionAroundRotation = CreateDefaultSubobject<USceneComponent>("PositionAroundRotation");
	PositionAroundRotation->SetupAttachment(GetRootComponent());
	
	PositionLeft = CreateDefaultSubobject<USceneComponent>("PositionLeft");
	PositionLeft->SetupAttachment(PositionAroundRotation);
	
	PositionRight = CreateDefaultSubobject<USceneComponent>("PositionRight");
	PositionRight->SetupAttachment(PositionAroundRotation);
	
	StaticMeshComponent->SetupAttachment(PositionAroundRotation);
}

void AEquilNode::SetNewState(const EquilibriumTypes::ENodeRotationState& NewRotationState)
{
	RotationState = NewRotationState;
}

void AEquilNode::BeginPlay()
{
	Super::BeginPlay();

	DesiredRotation = PositionAroundRotation->GetComponentRotation();
	NormalRotation = PositionAroundRotation->GetComponentRotation();
	NormalLeftRotation = GetPositionLeft()->GetComponentRotation();
	NormalRightRotation = GetPositionRight()->GetComponentRotation();
}

void AEquilNode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CalculateRotation(DeltaTime);
}

void AEquilNode::CalculateRotation(FRotator DesiredRotationToSet)
{
	DesiredRotation = DesiredRotationToSet;
}

void AEquilNode::CalculateRotation(float DeltaTime) const
{
	const FRotator InitialRotation = PositionAroundRotation->GetComponentRotation();
	const FRotator InitialLeftRotation = GetPositionLeft()->GetComponentRotation();
	const FRotator InitialRightRotation = GetPositionRight()->GetComponentRotation();
	
	if (InitialRotation != DesiredRotation)
	{
		const FRotator NewRotation = FMath::RInterpTo(InitialRotation, NormalRotation + DesiredRotation, DeltaTime, InterpSpeedTime);
		PositionAroundRotation->SetWorldRotation(NewRotation);
		
		const FRotator NewLeftRotation = FMath::RInterpTo(InitialLeftRotation, NormalLeftRotation, DeltaTime, InterpSpeedTime);
		GetPositionLeft()->SetWorldRotation(NewLeftRotation);

		const FRotator NewRightRotation = FMath::RInterpTo(InitialRightRotation, NormalRightRotation, DeltaTime, InterpSpeedTime);
		GetPositionRight()->SetWorldRotation(NewRightRotation);
	}
}

