#pragma once

#include "Commands.h"
#include "World.h"

namespace AlpinistGame
{
	class GameController
	{
		World* m_world;

	public:
		GameController();
		GameController(const std::vector<std::string>& map);

		bool MoveForward();
		bool RotateRight();
		bool RotateLeft();

		bool WallInDirection(Condition definition);

		World* GetWorld() { return m_world; }

		bool ExecuteMacroCommand(MacroCommand* MacroCommand);
	};
}
