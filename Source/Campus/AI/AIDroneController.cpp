// Fill out your copyright notice in the Description page of Project Settings.


#include "Campus/AI/AIDroneController.h"
#include "Campus/AI/AIDrone/CoreDrone/AIAnimDrone.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/Engine.h"
#include "Campus/AI/AIDrone/Components/AIDronePerceptionComponent.h"

AAIDroneController::AAIDroneController()
{
	AIDronePerceptionComponent = CreateDefaultSubobject<UAIDronePerceptionComponent>("AIDronePerceptionComponent");
	SetPerceptionComponent(*AIDronePerceptionComponent);
}

void AAIDroneController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const AAIAnimDrone* Drone = Cast< AAIAnimDrone>(InPawn);
	if (Drone)
	{
		RunBehaviorTree(Drone->BehaviorTreeAsset);
	}
}

void AAIDroneController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// GetPathFollowingComponent()->RequestMove();

	// фокус остаётся после окончания взаимодействия, придумать, где это заканчивать
	const AAIAnimDrone* Drone = Cast< AAIAnimDrone>(GetPawn());
	if (Drone->DoesHeInteract())
	{
		const auto AimCharacter = AIDronePerceptionComponent->GetInteractionCharacter();
		SetFocalPoint(AimCharacter->GetActorLocation());
	}
}


