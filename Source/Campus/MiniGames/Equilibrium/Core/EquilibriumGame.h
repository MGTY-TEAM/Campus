#pragma once

#include <iostream>
#include "Equilibrium.h"

using namespace std;

namespace EquilibriumGame
{
	enum EGameState
	{
		GS_UnPlaying = 0,
		GS_Playing = 1,
		GS_NotStart = 2
	};

	class GameEquilibrium
	{
	public:
		GameEquilibrium(const vector<vector<int>>& Cups);

		bool TryStartGame();

		bool EquilibriumIsValidByCups(const vector<vector<int>>& Cups) const;
		bool TryAddWeight(const vector<int>& Array, int Weight) const;
		bool TryRemoveWeight(const vector<int>& Array) const;
		bool CheckWin();

		Equilibrium GetEquilibriumInstance() const { return EquilibriumInstance; }
	private:
		Equilibrium EquilibriumInstance;
		EGameState GameState;
	};
}
