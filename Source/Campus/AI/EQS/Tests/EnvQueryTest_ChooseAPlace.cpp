// Fill out your copyright notice in the Description page of Project Settings.

#include "Campus/AI/EQS/Tests/EnvQueryTest_ChooseAPlace.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_ActorBase.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Campus/UserInterface/ChatBox.h"
#include "Campus/AI/AIDrone/CoreDrone/AIAnimDrone.h"
#include "Campus/Drone/TeleportationPlane.h"

UEnvQueryTest_ChooseAPlace::UEnvQueryTest_ChooseAPlace(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	Cost = EEnvTestCost::Low;
	ValidItemType = UEnvQueryItemType_ActorBase::StaticClass();
	SetWorkOnFloatValues(false);
}

void UEnvQueryTest_ChooseAPlace::RunTest(FEnvQueryInstance& QueryInstance) const
{
	const auto DataOwner = Cast<AActor>(QueryInstance.Owner.Get());
	BoolValue.BindData(DataOwner, QueryInstance.QueryID);
	const bool Switch = BoolValue.GetValue();

	UBlackboardComponent* const Blackboard = UAIBlueprintHelperLibrary::GetBlackboard(DataOwner);
	if (!Blackboard) return;

	AAIAnimDrone* const Drone = Cast<AAIAnimDrone>(Blackboard->GetValueAsObject(SelfActorKeyName));

	// Cast<ATeleportationPlane>(Drone->TeleportationPlaces[index]);

	for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
	{
		It.SetScore(TestPurpose, FilterType, It.GetIndex() == 1, Switch);
	}
}
