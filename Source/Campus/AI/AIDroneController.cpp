// Fill out your copyright notice in the Description page of Project Settings.


#include "Campus/AI/AIDroneController.h"
#include "Campus/AI/AIDrone/CoreDrone/AIAnimDrone.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/Engine.h"

void AAIDroneController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const AAIAnimDrone* Drone = Cast< AAIAnimDrone>(InPawn);
	if (Drone)
	{
		RunBehaviorTree(Drone->BehaviorTreeAsset);
	}
}


