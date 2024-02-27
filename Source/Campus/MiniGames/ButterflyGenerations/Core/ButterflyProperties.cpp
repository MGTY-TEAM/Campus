#include "ButterflyProperties.h"

using namespace ButterflyGenerationsGame;

ButterflyProperties::ButterflyProperties(const std::vector<uint8_t>& properties): WingShape(properties[0]), Pattern(properties[1]), Color(properties[2])
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
