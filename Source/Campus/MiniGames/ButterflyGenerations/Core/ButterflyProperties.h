#pragma once
namespace ButterflyGenerationsGame
{
	struct ButterflyProperties
	{
		uint8_t WingShape;
		uint8_t Pattern;
		uint8_t Color;
		
		ButterflyProperties(const std::vector<uint8_t>& properties);
		
		void ChangeProperties(const std::vector<uint8_t>& properties);
	};
}
