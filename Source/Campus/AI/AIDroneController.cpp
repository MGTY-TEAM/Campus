// Fill out your copyright notice in the Description page of Project Settings.


#include "Campus/AI/AIDroneController.h"
#include "Campus/AI/AIDrone/CoreDrone/AIAnimDrone.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/Engine.h"
#include "Campus/AI/AIDrone/Components/AIDronePerceptionComponent.h"
#include "Campus/Chat/ChatManager.h"
#include "Campus/Chat/ChatUserComponent.h"

AAIDroneController::AAIDroneController()
{
	AIDronePerceptionComponent = CreateDefaultSubobject<UAIDronePerceptionComponent>("AIDronePerceptionComponent");
	
	ChatUserComponent = CreateDefaultSubobject<UChatUserComponent>("ChatUserComponent");
	
	SetPerceptionComponent(*AIDronePerceptionComponent);
}

UChatUserComponent* AAIDroneController::GetChatComponent()
{
	return ChatUserComponent;
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

	// ����� ������� ����� ��������� ��������������, ���������, ��� ��� �����������
	const AAIAnimDrone* Drone = Cast< AAIAnimDrone>(GetPawn());
	if (Drone->DoesHeInteract())
	{
		const auto AimCharacter = AIDronePerceptionComponent->GetInteractionCharacter();
		// SetFocus(AimCharacter);
	}
}

void AAIDroneController::BeginPlay()
{
	Super::BeginPlay();

	if (ChatUserComponent)
	{
		ChatUserComponent->SetUserID("Bot");

		if (UChatManager::Get()->RegisterUser("Bot", ChatUserComponent))
		{
			UE_LOG(LogTemp, Warning, TEXT("Bot Chat Component is registered"));
		}
	}
}


