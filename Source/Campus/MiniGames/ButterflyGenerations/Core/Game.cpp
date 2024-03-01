#include "Game.h"

#include "GameExceptions.h"
using namespace ButterflyGenerationsGame;

Game::Game(): M_GameState(GS_NOT_STARTED)
{
}

Game::~Game()
{
	M_ButterflyGenerationRegistry = nullptr;
}

bool Game::TryStartGameWithPosition(const std::vector<uint8_t>& layers,
                                    const std::vector<InheritanceConnection>& connections)
{
	switch (M_GameState)
	{
	case GS_NOT_STARTED:
		M_ButterflyGenerationRegistry = std::make_unique<ButterflyGenerationRegistry>(layers, connections);
		M_GameState = GameState::GS_IN_PROGRESS;
		return true;
	default:
		throw GameException("Game is already in progress");
	}
}

bool Game::TryAddButterfly(const std::pair<uint8_t, uint8_t>& butterflyPosition,const std::vector<uint8_t>& butterflyProperties)
{
	switch (M_GameState)
	{
	case GameState::GS_IN_PROGRESS:
		M_ButterflyGenerationRegistry->AddButterfly(butterflyPosition, butterflyProperties);
		return true;
	default:
		return false;
	}
}

bool Game::TryRemoveButterfly(const std::pair<uint8_t, uint8_t> butterflyPosition)
{
	switch (M_GameState)
    {
    case GameState::GS_IN_PROGRESS:
        M_ButterflyGenerationRegistry->RemoveButterfly(butterflyPosition);
        return true;
    default:
    	return false;
    }
}

bool Game::TryValidateCurrentSolution() const
{
	switch (M_GameState)
	{
	case GameState::GS_IN_PROGRESS:
		return M_ButterflyGenerationRegistry->ValidateGenerations();;
	default:
		return false;
	}
}
