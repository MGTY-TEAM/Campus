
#include "Campus/MiniGames/Equilibrium/EquilibriumViewModelComponent.h"
#include "Campus/MiniGames/Equilibrium/EquilibriumView.h"
#include "Types/EquilCup.h"

DEFINE_LOG_CATEGORY_STATIC(LogEquilViewModel, All, All);

UEquilibriumViewModelComponent::UEquilibriumViewModelComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	// EquilibriumModelInstance = EquilibriumGame::GameEquilibrium();
}

void UEquilibriumViewModelComponent::BeginPlay()
{
	Super::BeginPlay();

	if (const AEquilibriumView* EquilibriumView = Cast<AEquilibriumView>(GetOwner()))
	{
		UE_LOG(LogEquilViewModel, Warning, TEXT("Component Has Parent"));
		for (const auto Cup : EquilibriumView->GetAllCups())
		{
			UE_LOG(LogEquilViewModel, Warning, TEXT("Cup Was Add To Delegate"));
			Cup->OnAttemptToAddWeight.AddUObject(this, &UEquilibriumViewModelComponent::OnTryAddWeight);
			Cup->OnAttemptToRemoveWeight.AddUObject(this, &UEquilibriumViewModelComponent::OnTryRemoveWeight);
		}
	}

	
}

void UEquilibriumViewModelComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UEquilibriumViewModelComponent::CreateModelInstance(const vector<vector<int32_t>>& Cups)
{
	EquilibriumModelInstance = EquilibriumGame::GameEquilibrium(Cups);
	EquilibriumModelInstance.TryStartGame();
}

void UEquilibriumViewModelComponent::OnTryAddWeight(const vector<int>& Array, int Weight) const
{
	if (EquilibriumModelInstance.TryAddWeight(Array, Weight))
	{
		UE_LOG(LogEquilViewModel, Warning, TEXT("Weight Was Added"));
		OnChangeStates.Broadcast(EquilibriumModelInstance.CheckState());
	}
}

void UEquilibriumViewModelComponent::OnTryRemoveWeight(const vector<int>& Array) const
{
	if (EquilibriumModelInstance.TryRemoveWeight(Array))
	{
		OnChangeStates.Broadcast(EquilibriumModelInstance.CheckState());
	}
}

