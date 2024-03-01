#include "EquilibriumTypes.h"

using namespace EquilibriumTypes;

// --------------------  BTNode  --------------------

EquilNode::EquilNode()
{
	RotationState = NRS_Stable;
}

int EquilNode::CalculateMass()
{
	const int LeftMass = GetLeftChild() ? GetLeftChild()->CalculateMass() : 0;
	const int RightMass = GetRightChild() ? GetRightChild()->CalculateMass() : 0;

	if (LeftMass == RightMass)
	{
		RotationState = NRS_Stable;
	}
	else if (LeftMass < RightMass)
	{
		RotationState = NRS_Right;
	}
	else
	{
		RotationState = NRS_Left;
	}

	return LeftMass + RightMass;
}

EquilElement::~EquilElement()
{
	
}

void EquilElement::SetLeftChild(EquilElement* Element)
{
	LeftChild = Element;
}

void EquilElement::SetRightChild(EquilElement* Element)
{
	RightChild = Element;
}

// ---------------------  BTCup  ---------------------

EquilCup::EquilCup()
{
	Weight = 0;
}

void EquilCup::AddWeight(int NewWeight)
{
	this->Weight = NewWeight;
}

void EquilCup::RemoveWeight()
{
	this->Weight = 0;
}

int EquilCup::CalculateMass()
{
	return GetMass();
}