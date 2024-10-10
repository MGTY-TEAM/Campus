#pragma once

#ifdef ALPINIST_GAME

#include "GameTypes.h"

namespace AlpinistGame
{
	class Entity;
	class Player;
	
	class World
	{
		std::vector<std::vector<TSharedPtr<Entity>>> m_grid;
		bool bFinished = false;
		TSharedPtr<Player> m_player;

		bool IsValidPosition(std::pair<int8_t, int8_t>) const;

	public:
		World(const std::vector<std::string>& grid);

		~World()
		{
		}
		TSharedPtr<Player> GetPlayer() { return m_player; }
		MoveResult SwapPlayerMove();

		friend std::ostream& operator<<(std::ostream& os, World* world);
		void LogWorld();
		bool WallInDirection(const Condition& condition);

		bool IsPlayerFinished() const { return bFinished; }

		void SetGrid(const std::vector<std::vector<TSharedPtr<Entity>>>& OldGrid);
		std::vector<std::vector<TSharedPtr<Entity>>> GetCopyOfGrid() const;
	};
}
#endif

/* TODO:
 * 1) Написать для каждой сущности конструкторы, методы копирования.
 * 

*/
