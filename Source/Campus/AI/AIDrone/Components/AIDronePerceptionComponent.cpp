// Fill out your copyright notice in the Description page of Project Settings.


#include "Campus/AI/AIDrone/Components/AIDronePerceptionComponent.h"
#include "Perception/AISense_Sight.h"
#include "Campus/AI/AIDroneController.h"
#include "Engine/Engine.h"

AActor* UAIDronePerceptionComponent::GetInteractionCharacter() const
{
	// �������� ������ a������ ���������, � ������� ��������������� ����

	TArray<AActor*> PerceiveActors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PerceiveActors);
	if (PerceiveActors.Num() == 0) return nullptr;

	const auto Controller = Cast<AAIDroneController>(GetOwner());
	if (!Controller) return nullptr;

	const auto Pawn = Controller->GetPawn();
	if (!Pawn) return nullptr;

	float BestDistance = MAX_FLT;
	AActor* OurPawn = nullptr;

	for (const auto PerceiveActor : PerceiveActors)
	{
		const auto CurrentDistance = (PerceiveActor->GetActorLocation() - Pawn->GetActorLocation()).Size();
		if (CurrentDistance < BestDistance)
		{
			OurPawn = PerceiveActor;
			BestDistance = CurrentDistance;
		}
	}

	return OurPawn;
}

bool UAIDronePerceptionComponent::CanISee(AActor* Actor)
{
	TArray<AActor*> PerceiveActors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PerceiveActors);
	if (PerceiveActors.Num() == 0) return false;

	for (const auto PerceiveActor : PerceiveActors)
	{
		if (PerceiveActor == Actor)
		{
			SetLastLocationOf(Actor);
			return true;
		}
	}

	return false;
}

void UAIDronePerceptionComponent::SetLastLocationOf(AActor* Actor)
{
	LastLocationOfInteractionCharacter = Actor->GetActorLocation();
}
