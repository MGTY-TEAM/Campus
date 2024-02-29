#include "Butterfly.h"
#include "ButterflyProperties.h"
using namespace ButterflyGenerationsGame;


Butterfly::Butterfly(const ButterflyProperties& butterflyProperties) : M_ButterflyProperties(butterflyProperties)
{
	
}
const ButterflyProperties& Butterfly::GetProperties() const
{
	return M_ButterflyProperties;
}



