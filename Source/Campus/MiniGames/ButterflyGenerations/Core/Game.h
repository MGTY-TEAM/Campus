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

		bool TryStartGameWithPosition(const std::vector<uint8_t>& layers, const std::vector<InheritanceConnection>& connections);
		bool TryAddButterfly(const std::pair<uint8_t, uint8_t>& butterflyPosition, const std::vector<uint8_t>& butterflyProperties);

		bool TryValidateCurrentSolution();
	
	private:
		std::unique_ptr<ButterflyGenerationRegistry> M_ButterflyGenerationRegistry;

		GameState M_GameState;
	};
}
