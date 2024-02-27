#include "Butterfly.h"

using namespace ButterflyGenerationsGame;

Butterfly::Butterfly(ButterflyGenerationsGame::ButterflyProperties butterflyProperties, Butterfly* firstParent,
	Butterfly* secondParent): M_ButterflyProperties(butterflyProperties),
	                          M_FirstParent(firstParent), M_SecondParent(secondParent)
{
	
}

const ButterflyProperties& Butterfly::GetProperties() const
{
	return M_ButterflyProperties;
}

void Butterfly::SetProperties(const ButterflyGenerationsGame::ButterflyProperties& butterflyProperties)
{
	M_ButterflyProperties = butterflyProperties;
}

bool Butterfly::IsParentsValid() const
{
	if (!M_FirstParent || !M_SecondParent)
		return true;

	const uint8_t firstParentColor = M_FirstParent->M_ButterflyProperties.Color;
	const uint8_t firstParentPattern = M_FirstParent->M_ButterflyProperties.Pattern;
	const uint8_t firstParentWingShape = M_FirstParent->M_ButterflyProperties.WingShape;

	const uint8_t secondParentColor = M_SecondParent->M_ButterflyProperties.Color;
	const uint8_t secondParentPattern = M_SecondParent->M_ButterflyProperties.Pattern;
	const uint8_t secondParentWingShape = M_SecondParent->M_ButterflyProperties.WingShape;

	if ((firstParentColor == M_ButterflyProperties.Color  || secondParentColor == M_ButterflyProperties.Color) &&
		(firstParentPattern == M_ButterflyProperties.Pattern || secondParentPattern == M_ButterflyProperties.Pattern) &&
        (firstParentWingShape == M_ButterflyProperties.WingShape || secondParentWingShape == M_ButterflyProperties.WingShape))
	{
		return true;
	}
	
	return false;
}


