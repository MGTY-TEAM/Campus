#include "ButterflyGenerationRegistry.h"

#include "GameExceptions.h"

using namespace ButterflyGenerationsGame;

ButterflyGenerationRegistry::ButterflyGenerationRegistry(
	std::vector<std::vector<Butterfly*>> generationLayers)
{
	if (generationLayers.empty())
		throw GameException("Generation layers cannot be empty.");

	M_GenerationLayers = generationLayers;
}

ButterflyGenerationRegistry::ButterflyGenerationRegistry(
	std::vector<std::tuple<std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>>>
	layers)
{
	for (std::tuple<std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>>
	     layer : layers)
	{
		std::vector<uint8_t> elementPosition = std::get<0>(layer);

		if (elementPosition.empty())
			throw GameException("Element position cannot be empty.");

		std::vector<uint8_t> elementProperties = std::get<1>(layer);
		if (elementProperties.empty() or elementProperties.size() != 3)
			throw GameException("Invalid properties.");
		
		std::vector<uint8_t> elementFirstParentPosition = std::get<2>(layer);
		if (elementFirstParentPosition.size() != 2)
			throw GameException("Invalid first parent position.");
		
		std::vector<uint8_t> elementSecondParentPosition = std::get<3>(layer);
		if (elementSecondParentPosition.size()!= 2)
			throw GameException("Invalid second parent position.");

		Butterfly* newElement; 
		if (elementFirstParentPosition.empty() || elementSecondParentPosition.empty())
			newElement = new Butterfly(elementProperties);
		else
			newElement = new Butterfly(elementProperties, M_GenerationLayers[elementFirstParentPosition.at(
				                           0)][elementFirstParentPosition.at(1)],
			                           M_GenerationLayers[elementSecondParentPosition.at(
				                           0)][elementSecondParentPosition.at(1)]);

		if (M_GenerationLayers.size() <= elementPosition.at(0))
			M_GenerationLayers.push_back(std::vector<Butterfly*>());

		M_GenerationLayers[elementPosition.at(0)].push_back(newElement);
	}
}

ButterflyGenerationRegistry::~ButterflyGenerationRegistry()
{
	for (std::vector<Butterfly*> layer : M_GenerationLayers)
	{
		for (Butterfly* element : layer)
		{
			delete element;
		}
	}
}

void ButterflyGenerationRegistry::AddButterfly(Butterfly* Butterfly, std::vector<uint8_t> position)
{
	if (Butterfly == nullptr || position.empty() || M_GenerationLayers.empty())
		throw GameException("Add butterfly failed");
	
	M_GenerationLayers.at(position.at(0)).at(position.at(1)) = Butterfly;
}

void ButterflyGenerationRegistry::AddButterfly(std::vector<uint8_t> butterflyPosition,
	std::vector<uint8_t> butterflyProperties, std::vector<uint8_t> firstParentPosition,
	std::vector<uint8_t> secondParentPosition)
{
	if (butterflyPosition.empty() || butterflyProperties.empty() || firstParentPosition.empty() ||
        secondParentPosition.empty())
        throw GameException("Add butterfly failed");

    M_GenerationLayers.at(butterflyPosition.at(0)).at(butterflyPosition.at(1)) = new Butterfly(
        butterflyProperties, M_GenerationLayers[firstParentPosition.at(0)][firstParentPosition.at(1)],
        M_GenerationLayers[secondParentPosition.at(0)][secondParentPosition.at(1)]);
}

bool ButterflyGenerationRegistry::IsGenerationsValid() const
{
	if (M_GenerationLayers.empty())
		throw GameException("Generation layers is empty");
	
	for (const std::vector<Butterfly*> generationLayer : M_GenerationLayers)
	{
		for (const Butterfly* element : generationLayer)
		{
			if (!element->IsParentsValid())
			{
				return false;
			}
		}
	}
	return true;
}
