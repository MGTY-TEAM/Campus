#pragma once
#include "Butterfly.h"

namespace ButterflyGenerationsGame
{
	class ButterflyGenerationRegistry
	{
	public:
		ButterflyGenerationRegistry(std::vector<std::vector<Butterfly*>> generationLayers);

		ButterflyGenerationRegistry(
			std::vector<std::tuple<std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>, std::vector<
				                       uint8_t>>> layers);

		~ButterflyGenerationRegistry();

		void AddButterfly(Butterfly* butterfly, std::vector<uint8_t> position);
		void AddButterfly(std::vector<uint8_t> butterflyPosition, std::vector<uint8_t> butterflyProperties,
		                  std::vector<uint8_t> firstParentPosition, std::vector<uint8_t> secondParentPosition);
		bool IsGenerationsValid() const;

	private:
		std::vector<std::vector<Butterfly*>> M_GenerationLayers;
	};
}
