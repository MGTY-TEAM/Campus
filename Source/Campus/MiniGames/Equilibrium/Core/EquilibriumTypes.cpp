#include "EquilibriumTypes.h"

using namespace EquilibriumTypes;

// --------------------  BTNode  --------------------

EquilNode::EquilNode()
{
	RotationState = NRS_Stable;
}

int32_t EquilNode::CalculateMass()
{
	const int32_t LeftMass = GetLeftChild() ? GetLeftChild()->CalculateMass() : 0;
	const int32_t RightMass = GetRightChild() ? GetRightChild()->CalculateMass() : 0;

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

void EquilCup::AddWeight(int32_t NewWeight)
{
	this->Weight = NewWeight;
}

void EquilCup::RemoveWeight()
{
	this->Weight = 0;
}

int32_t EquilCup::CalculateMass()
{
	return GetMass();
}