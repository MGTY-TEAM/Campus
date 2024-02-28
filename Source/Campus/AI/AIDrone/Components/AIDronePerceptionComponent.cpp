// Fill out your copyright notice in the Description page of Project Settings.


#include "Campus/AI/AIDrone/Components/AIDronePerceptionComponent.h"
#include "Perception/AISense_Sight.h"
#include "Campus/AI/AIDroneController.h"
#include "Engine/Engine.h"
#include "DrawDebugHelpers.h"
#include "CollisionQueryParams.h"

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

	if (std::any_of(PerceiveActors.begin(), PerceiveActors.end(), [&](const AActor* ActorP){ return Actor == ActorP; }))
	{
		SetLastLocationOf(Actor);
		return true;
	}

	return false;
}

void UAIDronePerceptionComponent::SetLastLocationOf(AActor* Actor)
{
	LastLocationOfInteractionCharacter = Actor->GetActorLocation();
}

bool UAIDronePerceptionComponent::CheckObstacleInFrontOfTarget(const AActor* Target) const
{
	const AAIController* Controller = Cast<AAIController>(GetOwner());
	if (!Controller) return false;
	
	const APawn* SelfPawn = Controller->GetPawn();
	if (!SelfPawn) return false;
	
	TArray<FHitResult> OutHits;
	const FVector& Start = SelfPawn->GetActorLocation();
	const FVector& End = Target->GetActorLocation();
	FCollisionObjectQueryParams QueryParams;
	QueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
	QueryParams.AddObjectTypesToQuery(ECC_Pawn);
	const FCollisionShape Sphere = FCollisionShape::MakeSphere(RadiusSphere);
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(SelfPawn);
	
	if (GetWorld()->SweepMultiByObjectType(OutHits, Start, End, FQuat::Identity, QueryParams, Sphere, Params))
	{
		if (OutHits.Num() == 1 && OutHits[0].GetActor() == Target)
		{
			// DrawDebugSphere(GetWorld(), OutHits[0].Location, RadiusSphere, 16, FColor::Green, false, 1.0f);
			return false;
		}
		// DrawDebugSphere(GetWorld(), OutHits[0].Location, RadiusSphere, 16, FColor::Red, false, 1.0f);
		return true;
	}
	
	return false;
}

void UAIDronePerceptionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}
