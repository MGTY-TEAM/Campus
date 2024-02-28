#include "ButterflyGenerationRegistry.h"

#include "GameExceptions.h"

using namespace ButterflyGenerationsGame;

void ButterflyGenerationRegistry::FillGenerationLayers(const std::vector<uint8_t>& layers)
{
	M_GenerationLayers.clear();
	M_GenerationLayers.resize(layers.size());

	for (size_t i = 0; i < layers.size(); i++)
	{
		M_GenerationLayers[i].resize(layers[i]);

		for (size_t j = 0; j < layers[i]; j++)
		{
			M_GenerationLayers[i][j] = new ButterflySlot();
		}
	}
}

void ButterflyGenerationRegistry::FillParentsConnections(const std::vector<InheritanceConnection>& parentsConnections)
{
	for (const InheritanceConnection& parentsConnection : parentsConnections)
	{
		M_GenerationLayers[parentsConnection.Child.first][parentsConnection.Child.second]->SetDependencySlots(
			M_GenerationLayers[parentsConnection.FirstParent.first][parentsConnection.FirstParent.second],
			M_GenerationLayers[parentsConnection.SecondParent.first][parentsConnection.SecondParent.second]);
	}
}

void ButterflyGenerationRegistry::AddButterfly(const std::pair<uint8_t, uint8_t>& position,
                                               const std::vector<uint8_t>& properties)
{
	M_GenerationLayers[position.first][position.second]->AddButterfly(new Butterfly(properties));
}

void ButterflyGenerationRegistry::RemoveButterfly(const std::pair<uint8_t, uint8_t>& position)
{
	M_GenerationLayers[position.first][position.second]->RemoveButterfly();
}

bool ButterflyGenerationRegistry::ValidateGenerations() const
{
	for (const std::vector<ButterflySlot*> generationLayer : M_GenerationLayers)
	{
		for (const ButterflySlot* element : generationLayer)
		{
			if (!element->IsValidDependency())
			{
				return false;
			}
		}
	}
	return true;
}
