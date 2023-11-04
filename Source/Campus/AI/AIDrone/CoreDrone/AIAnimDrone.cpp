// Fill out your copyright notice in the Description page of Project Settings.


#include "Campus/AI/AIDrone/CoreDrone/AIAnimDrone.h"
#include "Campus/AI/AIDroneController.h"

AAIAnimDrone::AAIAnimDrone()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AAIDroneController::StaticClass();
}
