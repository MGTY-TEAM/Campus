#include "Equilibrium.h"
#include "EquilibriumUtils.h"

using namespace EquilibriumGame;

// ------------------  Equilibrium  ------------------

Equilibrium::Equilibrium()
{
	Root = nullptr;
}

Equilibrium::Equilibrium(const Equilibrium& Other)
{
	Root = new EquilNode;
	Scales = Other.Scales;
	
	CopyEquilibrium(Other);
}


Equilibrium::Equilibrium(const vector<vector<int32_t>>& Cups)
{
	Root = new EquilNode;
	
	for (auto CupCoordinates : Cups)
	{
		Scales.push_back(CupCoordinates);
		EquilNode* Current = Root;
		while (CupCoordinates.size() - 1 != 0)
		{
			if (!Current) return;
			
			if (CupCoordinates[0] == 0)
			{
				if (Current->GetLeftChild() == nullptr)
				{
					Current->SetLeftChild(new EquilNode);
				}
				Current = dynamic_cast<EquilNode*>(Current->GetLeftChild());
			}
			else if (CupCoordinates[0] == 1)
			{
				if (Current->GetRightChild() == nullptr)
				{
					Current->SetRightChild(new EquilNode);
				}
				Current = dynamic_cast<EquilNode*>(Current->GetRightChild());
			}

			CupCoordinates.erase(CupCoordinates.begin());
		}

		if (CupCoordinates[0] == 0)
		{
			Current->SetLeftChild(new EquilCup);
		}
		else if (CupCoordinates[0] == 1)
		{
			Current->SetRightChild(new EquilCup);
		}
		CupCoordinates.clear();
	}
}

Equilibrium& Equilibrium::operator=(const Equilibrium& Other)
{
	if (&Other == this) return *this;
	
	Root = new EquilNode;
	Scales.clear();
	Scales = Other.Scales;
	
	CopyEquilibrium(Other);

	return *this;
}


ENodeRotationState Equilibrium::GetRootState() const
{
	return Root->GetRotationState();
}

void Equilibrium::CheckState(vector<ENodeRotationState>& NodeRotations) const
{
	if (Root)
	{
		CheckState(Root, NodeRotations);
	}
}

void Equilibrium::CheckState(const EquilNode* RootEquilNode, vector<ENodeRotationState>& NodeRotations) const
{
	switch (RootEquilNode->GetRotationState())
	{
	case NRS_Stable:
		NodeRotations.push_back(NRS_Stable);
		// cout << "Stable" << endl;
		break;
	case NRS_Left:
		NodeRotations.push_back(NRS_Left);
		// cout << "Left" << endl;
		break;
	case NRS_Right:
		NodeRotations.push_back(NRS_Right);
		// cout << "Right" << endl;
		break;
	default:
		break;
	}

	if (const EquilNode* NodeRoot = dynamic_cast<EquilNode*>(RootEquilNode->GetLeftChild()))
	{
		CheckState(NodeRoot, NodeRotations);
	}
	if (const EquilNode* NodeRoot = dynamic_cast<EquilNode*>(RootEquilNode->GetRightChild()))
	{
		CheckState(NodeRoot, NodeRotations);
	}
}

bool Equilibrium::IsValidByCups(const vector<vector<int32_t>>& Cups) const
{
	for (const auto& Cup : Cups)
	{
		if (!EquilibriumUtils::GetNeededElement(Cup, Root))
		{
			return false;
		}
	}
	return true;
}

bool Equilibrium::TryAddWeight(const vector<int32_t>& Array, int32_t Weight) const
{
	EquilElement* NeededElement = EquilibriumUtils::GetNeededElement(Array, Root);

	if (EquilCup* NeededCup = dynamic_cast<EquilCup*>(NeededElement))
	{
		NeededCup->AddWeight(Weight);
		Root->CalculateMass();
		return true;
	}
	return false;
 }

bool Equilibrium::TryRemoveWeight(const vector<int32_t>& Array) const
{
	EquilElement* NeededElement = EquilibriumUtils::GetNeededElement(Array, Root);

	if (EquilCup* NeededCup = dynamic_cast<EquilCup*>(NeededElement))
	{
		NeededCup->RemoveWeight();
		Root->CalculateMass();
		return true;
	}
	return false;
}

bool Equilibrium::EveryCupHasWeight() const
{
	return EveryCupHasWeight(Root);
}

bool Equilibrium::EveryNodeIsStable() const
{
	return EveryNodeIsStable(Root);
}

bool Equilibrium::EveryCupHasWeight(const EquilNode* RootEquilNode) const
{
	bool ResultLeft = true;
	bool ResultRight = true;

	if (const EquilNode* NodeRoot = dynamic_cast<EquilNode*>(RootEquilNode->GetLeftChild()))
	{
		ResultLeft = EveryCupHasWeight(NodeRoot);
	}
	else if (const EquilCup* Cup = dynamic_cast<EquilCup*>(RootEquilNode->GetLeftChild()))
	{
		if (Cup->GetMass() == 0)
		{
			return false;
		}
	}

	if (const EquilNode* NodeRoot = dynamic_cast<EquilNode*>(RootEquilNode->GetRightChild()))
	{
		ResultRight = EveryCupHasWeight(NodeRoot);
	}
	else if (const EquilCup* Cup = dynamic_cast<EquilCup*>(RootEquilNode->GetRightChild()))
	{
		if (Cup->GetMass() == 0)
		{
			return false;
		}
	}
	return ResultLeft && ResultRight;
}

bool Equilibrium::EveryNodeIsStable(const EquilNode* RootEquilNode) const
{
	bool ResultLeft = true;
	bool ResultRight = true;

	if (const EquilNode* NodeRoot = dynamic_cast<EquilNode*>(RootEquilNode->GetLeftChild()))
	{
		if (NodeRoot->GetRotationState() != NRS_Stable)
		{
			return false;
		}
		ResultLeft = EveryCupHasWeight(NodeRoot);
	}

	if (const EquilNode* NodeRoot = dynamic_cast<EquilNode*>(RootEquilNode->GetRightChild()))
	{
		if (NodeRoot->GetRotationState() != NRS_Stable)
		{
			return false;
		}
		ResultRight = EveryCupHasWeight(NodeRoot);
	}

	return ResultLeft && ResultRight;
}

void Equilibrium::CopyEquilibrium(const Equilibrium& Other) const
{
	for (auto CupCoordinates : Scales)
	{
		EquilNode* Current = Root;
		const EquilNode* CurrentOther = Other.Root;
		
		while (CupCoordinates.size() - 1 != 0)
		{
			if (!Current || !CurrentOther) continue;

			if (CupCoordinates[0] == 0)
			{
				if (Current->GetLeftChild() == nullptr)
				{
					Current->SetLeftChild(new EquilNode);
				}
				Current = dynamic_cast<EquilNode*>(Current->GetLeftChild());
				CurrentOther = dynamic_cast<EquilNode*>(CurrentOther->GetLeftChild());
			}
			else if (CupCoordinates[0] == 1)
			{
				if (Current->GetRightChild() == nullptr)
				{
					Current->SetRightChild(new EquilNode);
				}
				Current = dynamic_cast<EquilNode*>(Current->GetRightChild());
				CurrentOther = dynamic_cast<EquilNode*>(CurrentOther->GetRightChild());
			}

			CupCoordinates.erase(CupCoordinates.begin());
		}

		if (CupCoordinates[0] == 0)
		{
			Current->SetLeftChild(new EquilCup);

			if (EquilCup* CurrentCup = dynamic_cast<EquilCup*>(Current->GetLeftChild()))
			{
				CurrentCup->AddWeight(CurrentOther->GetLeftChild()->GetMass());
			}
		}
		else if (CupCoordinates[0] == 1)
		{
			Current->SetRightChild(new EquilCup);

			if (EquilCup* CurrentCup = dynamic_cast<EquilCup*>(Current->GetRightChild()))
			{
				CurrentCup->AddWeight(CurrentOther->GetRightChild()->GetMass());
			}
		}
		CupCoordinates.clear();
	}
	Root->CalculateMass();
}

