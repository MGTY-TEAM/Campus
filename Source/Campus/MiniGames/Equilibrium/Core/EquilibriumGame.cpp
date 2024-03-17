#include "EquilibriumGame.h"

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

void EquilibriumGame::GameEquilibrium::TryAddWeight(const vector<int32_t>& Array, int32_t Weight)
{
	if (GameState == GS_Playing || GameState == GS_Executed)
	{
		if (EquilibriumInstance.TryAddWeight(Array, Weight))
		{
			OnAddedWeight();
		}
	}
}

void EquilibriumGame::GameEquilibrium::TryRemoveWeight(const vector<int32_t>& Array)
{
	if (GameState == GS_Playing || GameState == GS_Executed)
	{
		if (EquilibriumInstance.TryRemoveWeight(Array))
		{
			OnRemovedWeight();
		}
	}
}

bool EquilibriumGame::GameEquilibrium::CheckWin()
{
	if (GameState == GS_Playing)
	{
		// EquilibriumInstance.CheckState();
		if (EquilibriumInstance.EveryNodeIsStable() && EquilibriumInstance.EveryCupHasWeight())
		{
			OnGameEnded();
			GameState = GS_Executed;
			return true;
		}
		return false;
	}
	return false;
}

vector<ENodeRotationState> EquilibriumGame::GameEquilibrium::CheckState()
{
	vector<ENodeRotationState> NodeRotations;

	EquilibriumInstance.CheckState(NodeRotations);

	if (GameState == GS_Playing)
	{
		CheckWin();
	}
	
	return NodeRotations;
}
