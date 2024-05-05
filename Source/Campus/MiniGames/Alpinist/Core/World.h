#pragma once

#include "Entities.h"
#include "GameTypes.h"

namespace AlpinistGame
{
	class World
	{
		std::vector<std::vector<Entity*>> m_grid;

		Player* m_player;

		bool IsValidPosition(std::pair<int8_t, int8_t>) const;

	public:
		World(const std::vector<std::string>& grid);

		~World()
		{
		};
		Player* GetPlayer() { return m_player; }
		MoveResult SwapPlayerMove();

		friend std::ostream& operator<<(std::ostream& os, World* world);
		bool WallInDirection(Condition condition);
	};
}
