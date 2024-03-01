#include "EquilibriumGame.h"

EquilibriumGame::GameEquilibrium::GameEquilibrium(const vector<vector<int>>& Cups)
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

bool EquilibriumGame::GameEquilibrium::EquilibriumIsValidByCups(const vector<vector<int>>& Cups) const
{
	return EquilibriumInstance.IsValidByCups(Cups);
}

bool EquilibriumGame::GameEquilibrium::TryAddWeight(const vector<int>& Array, int Weight) const
{
	if (GameState == GS_Playing)
	{
		return EquilibriumInstance.TryAddWeight(Array, Weight);
	}
	return false;
}

bool EquilibriumGame::GameEquilibrium::TryRemoveWeight(const vector<int>& Array) const
{
	if (GameState == GS_Playing)
	{
		return EquilibriumInstance.TryRemoveWeight(Array);
	}
	return false;
}

bool EquilibriumGame::GameEquilibrium::CheckWin()
{
	if (GameState == GS_Playing)
	{
		EquilibriumInstance.CheckState();
		if (EquilibriumInstance.EveryNodeIsStable() && EquilibriumInstance.EveryCupHasWeight())
		{
			GameState = GS_UnPlaying;
			return true;
		}
		return false;
	}
	return false;
}
