#pragma once

#include <iostream>
#include "vector"
#include "EquilibriumTypes.h"

using namespace std;
using namespace EquilibriumTypes;

namespace EquilibriumGame
{
	class Equilibrium
	{
	public:
		Equilibrium();
		Equilibrium(const vector<vector<int>>& Cups);
		bool TryAddWeight(const vector<int>& Array, int Weight) const;
		bool TryRemoveWeight(const vector<int>& Array) const;

		ENodeRotationState GetRootState() const;
		void CheckState() const;

		bool IsValidByCups(const vector<vector<int>>& Cups) const;
		bool EveryCupHasWeight() const;
		bool EveryNodeIsStable() const;
	private:
		EquilNode* Root;

		void CheckState(EquilNode* Root) const;
		bool EveryCupHasWeight(EquilNode* Root) const;
		bool EveryNodeIsStable(EquilNode* Root) const;
	};
}
