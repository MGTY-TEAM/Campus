#include "Game.h"

#include "GameExceptions.h"
using namespace ButterflyGenerationsGame;

Game::Game(): M_GameState(GameState::GS_NOT_STARTED)
{
}

bool Game::TryStartGameWithPosition(
	std::vector<std::tuple<std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>>>
	layers)
{
	switch (M_GameState)
	{
	case GS_NOT_STARTED:
		M_ButterflyGenerationRegistry = std::make_unique<ButterflyGenerationRegistry>(layers);
		M_GameState = GameState::GS_IN_PROGRESS;
		return true;
	default:
		throw GameException("Game is already in progress");
	}
}

bool Game::TryAddButterfly(std::vector<uint8_t> butterflyPosition, std::vector<uint8_t> butterflyProperties,
                           std::vector<uint8_t> firstParentPosition, std::vector<uint8_t> secondParentPosition)
{
	switch (M_GameState)
	{
	case GameState::GS_IN_PROGRESS:
		M_ButterflyGenerationRegistry->AddButterfly(butterflyPosition, butterflyProperties, firstParentPosition,
		                                            secondParentPosition);
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
		return M_ButterflyGenerationRegistry->IsGenerationsValid();;
	case GameState::GS_NOT_STARTED:
		throw GameException("Game is not started");
	case GameState::GS_ENDED:
		throw GameException("Game is already ended");
	default:
		throw GameException("Unknown game error");
	}
}
