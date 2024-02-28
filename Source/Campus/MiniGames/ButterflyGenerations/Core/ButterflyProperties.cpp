#include "ButterflyProperties.h"

using namespace ButterflyGenerationsGame;

ButterflyProperties::ButterflyProperties(const std::vector<uint8_t>& properties): WingShape(properties.at(0)), Pattern(properties.at(1)),
																 Color(properties.at(2))
{
	
	
}

void ButterflyProperties::ChangeProperties(const std::vector<uint8_t>& properties)
{
	if (!properties.empty())
	{
		WingShape = properties.at(0);
		Pattern = properties.at(1);
		Color = properties.at(2);
	}
}

bool ButterflyProperties::IsValidPropertiesChildToParents(const ButterflyProperties& child,
	const ButterflyProperties& firstParent, const ButterflyProperties& secondParent)
{
	return (child.Color == firstParent.Color || child.Color == secondParent.Color) && (child.Pattern ==
		firstParent.Pattern || child.Pattern == secondParent.Pattern) && (child.WingShape == firstParent.
		WingShape || child.WingShape == secondParent.WingShape);
}
