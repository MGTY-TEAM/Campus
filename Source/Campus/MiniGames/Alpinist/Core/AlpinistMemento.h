#pragma once

#include "World.h"
#include <unordered_map>
// #include "Commands.h"
// #include "GameController.h"

#ifdef ALPINIST_GAME

namespace AlpinistGame
{
	class PlayerCommand;
	// class GameController;

	class BaseMemento
	{
	public:

		virtual ~BaseMemento() {};
	protected:
		BaseMemento() {};
	private:
		virtual void SetState(const std::vector<std::vector<TSharedPtr<Entity>>>& StateGrid) = 0;
		virtual const std::vector<std::vector<TSharedPtr<Entity>>>& GetState() = 0;
	};

	class AlpinistMemento : public BaseMemento
	{
	public:
		friend class GameController;
		virtual ~AlpinistMemento() override {};
	private:
		AlpinistMemento() {};

		virtual void SetState(const std::vector<std::vector<TSharedPtr<Entity>>>& StateGrid) override;
		virtual const std::vector<std::vector<TSharedPtr<Entity>>>& GetState() override { return m_grid; };

		std::vector<std::vector<TSharedPtr<Entity>>> m_grid;
	};

	class AlpinistCaretaker
	{
		std::vector<std::pair<PlayerCommand*, BaseMemento*>> m_vectorMementos;
	public:
		AlpinistCaretaker() {};
	
		void Backup(AlpinistMemento*& NewMemento, PlayerCommand*& Command);
		AlpinistMemento* Undo(PlayerCommand*& Command);
	};
}
#endif
