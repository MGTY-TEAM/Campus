#include "EquilibriumGame.h"

DEFINE_LOG_CATEGORY_STATIC(LogEquilGameModel, All, All);

EquilibriumGame::GameEquilibrium::GameEquilibrium()
{
	EquilibriumInstance = Equilibrium();
	GameState = GS_UnPlaying;
}

EquilibriumGame::GameEquilibrium::GameEquilibrium(const vector<vector<int32_t>>& Cups)
{
	EquilibriumInstance = Equilibrium(Cups);
	GameState = GS_UnPlaying;
}

bool EquilibriumGame::GameEquilibrium::TryStartGame()
{
	if (GameState != GS_NotStart)
	{
		GameState = GS_Playing;
		return true;
	}
	return false;
}

bool EquilibriumGame::GameEquilibrium::EquilibriumIsValidByCups(const vector<vector<int32_t>>& Cups) const
{
	return EquilibriumInstance.IsValidByCups(Cups);
}

bool EquilibriumGame::GameEquilibrium::TryAddWeight(const vector<int32_t>& Array, int32_t Weight) const
{
	if (GameState == GS_Playing)
	{
		UE_LOG(LogEquilGameModel, Warning, TEXT("EquilGameModel Trying To Add Weight"));
		return EquilibriumInstance.TryAddWeight(Array, Weight);
	}
	UE_LOG(LogEquilGameModel, Warning, TEXT("EquilGameModel Cann't Add Weight"));
	return false;
}

bool EquilibriumGame::GameEquilibrium::TryRemoveWeight(const vector<int32_t>& Array) const
{
	if (GameState == GS_Playing)
	{
		UE_LOG(LogEquilGameModel, Warning, TEXT("EquilGameModel Trying To Remove Weight"));
		return EquilibriumInstance.TryRemoveWeight(Array);
	}
	UE_LOG(LogEquilGameModel, Warning, TEXT("EquilGameModel Cann't Remove Weight"));
	return false;
}

bool EquilibriumGame::GameEquilibrium::CheckWin()
{
	if (GameState == GS_Playing)
	{
		// EquilibriumInstance.CheckState();
		if (EquilibriumInstance.EveryNodeIsStable() && EquilibriumInstance.EveryCupHasWeight())
		{
			GameState = GS_UnPlaying;
			return true;
		}
		return false;
	}
	return false;
}

vector<ENodeRotationState> EquilibriumGame::GameEquilibrium::CheckState() const
{
	vector<ENodeRotationState> NodeRotations;

	EquilibriumInstance.CheckState(NodeRotations);
	
	return NodeRotations;
}
