
#include "Campus/MiniGames/Equilibrium/EquilibriumViewModelComponent.h"
#include "Campus/MiniGames/Equilibrium/EquilibriumView.h"
#include "Types/EquilCup.h"

using namespace EquilibriumGame;

UEquilibriumViewModelComponent::UEquilibriumViewModelComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	EquilibriumGameModelInstance = nullptr;
}

void UEquilibriumViewModelComponent::BeginPlay()
{
	Super::BeginPlay();

	if (const AEquilibriumView* EquilibriumView = Cast<AEquilibriumView>(GetOwner()))
	{
		for (const auto Cup : EquilibriumView->GetAllCups())
		{
			Cup->OnAttemptToAddWeight.AddUObject(this, &UEquilibriumViewModelComponent::OnTryAddWeight);
			Cup->OnAttemptToRemoveWeight.AddUObject(this, &UEquilibriumViewModelComponent::OnTryRemoveWeight);
		}
	}
}

void UEquilibriumViewModelComponent::CreateModelInstance(const vector<vector<int32_t>>& Cups)
{
	EquilibriumGameModelInstance = new GameEquilibrium(Cups);
	EquilibriumGameModelInstance->TryStartGame();
	EquilibriumGameModelInstance->OnGameEnded += METHOD_HANDLER(*this, UEquilibriumViewModelComponent::OnGameEnded);
	EquilibriumGameModelInstance->OnAddedWeight += METHOD_HANDLER(*this, UEquilibriumViewModelComponent::OnAddedWeight);
	EquilibriumGameModelInstance->OnRemovedWeight += METHOD_HANDLER(*this, UEquilibriumViewModelComponent::OnRemovedWeight);

	OnTryAddWeightInModel += METHOD_HANDLER(*EquilibriumGameModelInstance, GameEquilibrium::TryAddWeight);
	OnTryRemoveWeightInModel += METHOD_HANDLER(*EquilibriumGameModelInstance, GameEquilibrium::TryRemoveWeight);
}

void UEquilibriumViewModelComponent::OnTryAddWeight(const vector<int32_t>& Array, int32_t Weight) const
{
	OnTryAddWeightInModel(Array, Weight);
}

void UEquilibriumViewModelComponent::OnTryRemoveWeight(const vector<int32_t>& Array) const
{
	OnTryRemoveWeightInModel(Array);
}

void UEquilibriumViewModelComponent::OnAddedWeight()
{
	OnChangeStates.Broadcast(EquilibriumGameModelInstance->CheckState());
}

void UEquilibriumViewModelComponent::OnRemovedWeight()
{
	OnChangeStates.Broadcast(EquilibriumGameModelInstance->CheckState());
}

void UEquilibriumViewModelComponent::OnGameEnded()
{
	ExecuteMiniGameCompleted.Broadcast();
	UE_LOG(LogTemp, Log, TEXT("EQUILIBRIUM GAME ENDED"));
}

