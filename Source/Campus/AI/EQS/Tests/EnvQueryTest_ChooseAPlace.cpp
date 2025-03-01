// Fill out your copyright notice in the Description page of Project Settings.

#include "Campus/AI/EQS/Tests/EnvQueryTest_ChooseAPlace.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_ActorBase.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Campus/AI/AIDrone/CoreDrone/AIAnimDrone.h"

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

	for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
	{
		const int32 ActionPlace = Blackboard->GetValueAsInt(ActionPlaceKeyName);

		if (Drone->TeleportationPlaces.IsValidIndex(ActionPlace - 1))
		{
			It.SetScore(TestPurpose, FilterType, Drone->TeleportationPlaces[It.GetIndex()] == Drone->TeleportationPlaces[ActionPlace - 1], Switch);
			UE_LOG(LogTemp, Error, TEXT("Current Location Current %s, Selected %s, State %i"), *Drone->TeleportationPlaces[It.GetIndex()]->GetActorNameOrLabel(), *Drone->TeleportationPlaces[ActionPlace - 1]->GetActorNameOrLabel(), Drone->TeleportationPlaces[It.GetIndex()] == Drone->TeleportationPlaces[ActionPlace - 1]);
		}
	}
}
