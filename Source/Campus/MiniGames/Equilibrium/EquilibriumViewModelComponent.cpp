
#include "Campus/MiniGames/Equilibrium/EquilibriumViewModelComponent.h"
#include "Campus/MiniGames/Equilibrium/EquilibriumView.h"
#include "Types/EquilCup.h"

using namespace EquilibriumGame;

UEquilibriumViewModelComponent::UEquilibriumViewModelComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
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
	EquilibriumGameModelInstance = EquilibriumGame::GameEquilibrium(Cups);
	EquilibriumGameModelInstance.TryStartGame();
	EquilibriumGameModelInstance.OnGameEnded += METHOD_HANDLER(*this, UEquilibriumViewModelComponent::OnGameEnded);
}

void UEquilibriumViewModelComponent::OnTryAddWeight(const vector<int>& Array, int Weight)
{
	if (EquilibriumGameModelInstance.TryAddWeight(Array, Weight))
	{
		OnChangeStates.Broadcast(EquilibriumGameModelInstance.CheckState());
		if (EquilibriumGameModelInstance.CheckWin())
		{
			ExecuteMiniGameCompleted.Broadcast();
		}
	}
}

void UEquilibriumViewModelComponent::OnTryRemoveWeight(const vector<int>& Array) const
{
	if (EquilibriumGameModelInstance.TryRemoveWeight(Array))
	{
		OnChangeStates.Broadcast(EquilibriumGameModelInstance.CheckState());
	}
}

void UEquilibriumViewModelComponent::OnGameEnded()
{
	UE_LOG(LogTemp, Warning, TEXT("GAME ENDED"));
}

