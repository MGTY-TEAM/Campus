#pragma once
#include "ButterflyProperties.h"


namespace ButterflyGenerationsGame
{
	class Butterfly
	{
	public:
		Butterfly(ButterflyProperties butterflyProperties);
		
		const ButterflyProperties& GetProperties() const;
		
	private:
		ButterflyProperties M_ButterflyProperties;
	};
}
