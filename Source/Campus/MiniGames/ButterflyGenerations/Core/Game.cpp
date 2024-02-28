#include "Game.h"

#include "GameExceptions.h"
using namespace ButterflyGenerationsGame;

Game::Game(): M_GameState(GS_NOT_STARTED)
{
}

Game::~Game()
{
	delete M_ButterflyGenerationRegistry;
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
	case GameState::GS_NOT_STARTED:
		throw GameException("Game is not started");
	case GameState::GS_ENDED:
		throw GameException("Game is already ended");
	default:
		throw GameException("Unknown game error");
	}
}

bool Game::TryValidateCurrentSolution()
{
	switch (M_GameState)
	{
	case GameState::GS_IN_PROGRESS:
		return M_ButterflyGenerationRegistry->ValidateGenerations();;
	case GameState::GS_NOT_STARTED:
		throw GameException("Game is not started");
	case GameState::GS_ENDED:
		throw GameException("Game is already ended");
	default:
		throw GameException("Unknown game error");
	}
}
