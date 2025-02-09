#pragma once
#include "ButterflyProperties.h"


namespace ButterflyGenerationsGame
{
	class Butterfly
	{
	public:
		Butterfly(const ButterflyProperties& butterflyProperties);
		
		const ButterflyProperties& GetProperties() const;
		
	private:
		ButterflyProperties M_ButterflyProperties;
	};
}
