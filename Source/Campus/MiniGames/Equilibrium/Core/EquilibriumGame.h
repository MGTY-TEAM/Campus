#pragma once

#include <iostream>
#include "Equilibrium.h"
#include "EventSystem/EquilibBaseEventClasses.h"

using namespace std;

namespace EquilibriumGame
{
	enum EGameState
	{
		GS_UnPlaying = 0,
		GS_Playing = 1,
		GS_Executed = 2,
		GS_NotStart = 3
	};

	class GameEquilibrium
	{
	public:
		GameEquilibrium();
		GameEquilibrium(const vector<vector<int32_t>>& Cups);

		TEvent<> OnGameEnded;
		
		bool TryStartGame();

		bool EquilibriumIsValidByCups(const vector<vector<int32_t>>& Cups) const;
		bool TryAddWeight(const vector<int32_t>& Array, int32_t Weight) const;
		bool TryRemoveWeight(const vector<int32_t>& Array) const;
		bool CheckWin();

		vector<ENodeRotationState> CheckState() const;
		Equilibrium GetEquilibriumInstance() const { return EquilibriumInstance; }
	private:
		Equilibrium EquilibriumInstance;
		EGameState GameState;
	};
}
