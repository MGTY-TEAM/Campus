#pragma once
#include "ButterflyGenerationRegistry.h"
#include "GameEnums.h"


namespace ButterflyGenerationsGame
{
	class Game
	{
	public:
		Game();
		~Game();

		bool TryStartGameWithPosition(
			std::vector<std::tuple<std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>, std::vector<
				                       uint8_t>>> layers);
		bool TryAddButterfly(std::vector<uint8_t> butterflyPosition, std::vector<uint8_t> butterflyProperties,
		                     std::vector<uint8_t> firstParentPosition, std::vector<uint8_t> secondParentPosition);

		bool TryValidateCurrentSolution();
	private:
		std::unique_ptr<ButterflyGenerationRegistry> M_ButterflyGenerationRegistry;

		GameState M_GameState;
	};
}
