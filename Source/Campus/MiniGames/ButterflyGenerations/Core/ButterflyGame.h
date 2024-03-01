#pragma once
#include "ButterflyGenerationRegistry.h"
#include "GameEnums.h"


namespace ButterflyGenerationsGame
{
	class ButterflyGame
	{
	public:
		ButterflyGame();
		~ButterflyGame();
		
		bool TryStartGameWithPosition(const std::vector<uint8_t>& layers, const std::vector<InheritanceConnection>& connections);
		bool TryAddButterfly(const std::pair<uint8_t, uint8_t>& butterflyPosition, const std::vector<uint8_t>& butterflyProperties);
		bool TryRemoveButterfly(const std::pair<uint8_t, uint8_t> butterflyPosition);
		bool TryValidateCurrentSolution() const ;
	
	private:
		std::unique_ptr<ButterflyGenerationRegistry> M_ButterflyGenerationRegistry;

		GameState M_GameState;
	}; 
}
