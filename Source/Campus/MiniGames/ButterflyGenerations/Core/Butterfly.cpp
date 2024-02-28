#include "Butterfly.h"
#include "ButterflyProperties.h"
using namespace ButterflyGenerationsGame;


Butterfly::Butterfly(ButterflyProperties butterflyProperties)
{
	M_ButterflyProperties = ButterflyProperties(butterflyProperties);
}

const ButterflyProperties& Butterfly::GetProperties() const
{
	return M_ButterflyProperties;
}



