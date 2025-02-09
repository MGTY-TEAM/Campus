#pragma once
#include "Butterfly.h"
#include "ButterflySlot.h"
#include "InheritanceConnection.h"

namespace ButterflyGenerationsGame
{
	class ButterflyGenerationRegistry
	{
	public:
		ButterflyGenerationRegistry(const std::vector<uint8_t>& layers,
		                            const std::vector<InheritanceConnection>& connections)
		{
			FillGenerationLayers(layers);
			FillParentsConnections(connections);
		}

		void AddButterfly(const std::pair<uint8_t, uint8_t>& position, const std::vector<uint8_t>& properties);

		void RemoveButterfly(const std::pair<uint8_t, uint8_t>& position);

		bool ValidateGenerations() const;

	private:
		void FillGenerationLayers(const std::vector<uint8_t>& layers);

		void FillParentsConnections(const std::vector<InheritanceConnection>& parentsConnections);
		std::vector<std::vector<ButterflySlot*>> M_GenerationLayers;
	};
}
