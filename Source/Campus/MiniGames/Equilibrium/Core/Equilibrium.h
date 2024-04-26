#pragma once

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
		Equilibrium(const Equilibrium& Other);
		explicit Equilibrium(const vector<vector<int32_t>>& Cups);
		bool TryAddWeight(const vector<int32_t>& Array, int32_t Weight) const;
		bool TryRemoveWeight(const vector<int32_t>& Array) const;

		ENodeRotationState GetRootState() const;
		void CheckState(vector<ENodeRotationState>& NodeRotations) const;

		bool IsValidByCups(const vector<vector<int32_t>>& Cups) const;
		bool EveryCupHasWeight() const;
		bool EveryNodeIsStable() const;

		Equilibrium& operator= (const Equilibrium& Other);
	private:
		EquilNode* Root;
		vector<vector<int32_t>> Scales;

		void CheckState(const EquilNode* Root, vector<ENodeRotationState>& NodeRotations) const;
		bool EveryCupHasWeight(const EquilNode* Root) const;
		bool EveryNodeIsStable(const EquilNode* Root) const;

		void CopyEquilibrium(const Equilibrium& Other) const;
	};
}
