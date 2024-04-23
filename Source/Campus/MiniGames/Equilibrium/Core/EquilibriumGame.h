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
		GameEquilibrium() : EquilibriumInstance(Equilibrium()), GameState(GS_UnPlaying) {};
		explicit GameEquilibrium(const vector<vector<int32_t>>& Cups) : EquilibriumInstance(Equilibrium(Cups)), GameState(GS_UnPlaying) {};

		mutable TEvent<> OnAddedWeight;
		mutable TEvent<> OnRemovedWeight;
		mutable TEvent<> OnGameEnded;
		
		bool TryStartGame();

		bool EquilibriumIsValidByCups(const vector<vector<int32_t>>& Cups) const;
		void TryAddWeight(const vector<int32_t>& Array, int32_t Weight);
		void TryRemoveWeight(const vector<int32_t>& Array);
		bool CheckWin();

		vector<ENodeRotationState> CheckState();
		Equilibrium* GetEquilibriumInstance() { return &EquilibriumInstance; }
	private:
		Equilibrium EquilibriumInstance;
		EGameState GameState;
	};
}
