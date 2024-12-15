#pragma once
#include "stdexcept"

namespace ButterflyGenerationsGame
{
	class GameException : public std::runtime_error {
	public:
		GameException(const std::string& message)
			: std::runtime_error(message) {}
	};
}
