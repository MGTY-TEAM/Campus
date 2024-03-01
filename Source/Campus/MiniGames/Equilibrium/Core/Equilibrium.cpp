#include "Equilibrium.h"
#include "EquilibriumUtils.h"

using namespace EquilibriumGame;

// ------------------  Equilibrium  ------------------

Equilibrium::Equilibrium()
{
	Root = new EquilNode;

	// Root->SetLeftChild(new EquilCup);
	// Root->SetRightChild(new EquilCup);
}

Equilibrium::Equilibrium(const vector<vector<int>>& Cups)
{
	Root = new EquilNode;

	for (auto CupCoordinates : Cups)
	{
		EquilNode* Current = Root;
		while ((CupCoordinates.size() - 1) != 0)
		{
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

ENodeRotationState Equilibrium::GetRootState() const
{
	return Root->GetRotationState();
}

void Equilibrium::CheckState() const
{
	if (Root)
	{
		CheckState(Root);
	}
}

bool Equilibrium::IsValidByCups(const vector<vector<int>>& Cups) const
{
	for (const auto Cup : Cups)
	{
		if (!EquilibriumUtils::GetNeededElement(Cup, Root))
		{
			return false;
		}
	}
	return true;
}

void Equilibrium::CheckState(EquilNode* RootEquilNode) const
{
	switch (RootEquilNode->GetRotationState())
	{
	case NRS_Stable:
		cout << "Stable" << endl;
		break;
	case NRS_Left:
		cout << "Left" << endl;
		break;
	case NRS_Right:
		cout << "Right" << endl;
		break;
	default:
		break;
	}

	if (EquilNode* NodeRoot = dynamic_cast<EquilNode*>(RootEquilNode->GetLeftChild()))
	{
		CheckState(NodeRoot);
	}
	if (EquilNode* NodeRoot = dynamic_cast<EquilNode*>(RootEquilNode->GetRightChild()))
	{
		CheckState(NodeRoot);
	}
}

bool Equilibrium::TryAddWeight(const vector<int>& Array, int Weight) const
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

bool Equilibrium::TryRemoveWeight(const vector<int>& Array) const
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

bool Equilibrium::EveryCupHasWeight(EquilNode* RootEquilNode) const
{
	bool ResultLeft = true;
	bool ResultRight = true;

	if (EquilNode* NodeRoot = dynamic_cast<EquilNode*>(RootEquilNode->GetLeftChild()))
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

	if (EquilNode* NodeRoot = dynamic_cast<EquilNode*>(RootEquilNode->GetRightChild()))
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

bool Equilibrium::EveryNodeIsStable(EquilNode* RootEquilNode) const
{
	bool ResultLeft = true;
	bool ResultRight = true;

	if (EquilNode* NodeRoot = dynamic_cast<EquilNode*>(RootEquilNode->GetLeftChild()))
	{
		if (NodeRoot->GetRotationState() != NRS_Stable)
		{
			return false;
		}
		ResultLeft = EveryCupHasWeight(NodeRoot);
	}

	if (EquilNode* NodeRoot = dynamic_cast<EquilNode*>(RootEquilNode->GetRightChild()))
	{
		if (NodeRoot->GetRotationState() != NRS_Stable)
		{
			return false;
		}
		ResultRight = EveryCupHasWeight(NodeRoot);
	}

	return ResultLeft && ResultRight;
}

