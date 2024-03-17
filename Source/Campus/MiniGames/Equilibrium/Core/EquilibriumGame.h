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

		TEvent<> OnAddedWeight;
		TEvent<> OnRemovedWeight;
		TEvent<> OnGameEnded;
		
		bool TryStartGame();

		bool EquilibriumIsValidByCups(const vector<vector<int32_t>>& Cups) const;
		void TryAddWeight(const vector<int32_t>& Array, int32_t Weight);
		void TryRemoveWeight(const vector<int32_t>& Array);
		bool CheckWin();

		vector<ENodeRotationState> CheckState();
		Equilibrium GetEquilibriumInstance() const { return EquilibriumInstance; }
	private:
		Equilibrium EquilibriumInstance;
		EGameState GameState;
	};
}
