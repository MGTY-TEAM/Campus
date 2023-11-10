// Fill out your copyright notice in the Description page of Project Settings.


#include "Campus/AI/Services/CharacterFocusService.h"
#include "Campus/AI/AIDrone/CoreDrone/AIAnimDrone.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Campus/AI/AIDroneController.h"
#include "Engine/Engine.h"

UCharacterFocusService::UCharacterFocusService()
{
	NodeName = "Focus On Character";
}

void UCharacterFocusService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAIDroneController* Controller = Cast<AAIDroneController>(OwnerComp.GetAIOwner());
	const UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (Blackboard)
	{
		AAIAnimDrone* AimActor = Cast<AAIAnimDrone>(Blackboard->GetValueAsObject(CharacterActorKey.SelectedKeyName));
		if (AimActor)
		{
			Controller->SetFocalPoint(AimActor->GetActorLocation());
		}
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
