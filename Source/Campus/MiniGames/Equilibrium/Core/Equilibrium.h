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
		Equilibrium(const vector<vector<int32_t>>& Cups);
		bool TryAddWeight(const vector<int32_t>& Array, int32_t Weight) const;
		bool TryRemoveWeight(const vector<int32_t>& Array) const;

		ENodeRotationState GetRootState() const;
		void CheckState(vector<ENodeRotationState>& NodeRotations) const;

		bool IsValidByCups(const vector<vector<int32_t>>& Cups) const;
		bool EveryCupHasWeight() const;
		bool EveryNodeIsStable() const;
	private:
		EquilNode* Root;

		void CheckState(EquilNode* Root, vector<ENodeRotationState>& NodeRotations) const;
		bool EveryCupHasWeight(EquilNode* Root) const;
		bool EveryNodeIsStable(EquilNode* Root) const;
	};
}
