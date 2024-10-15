

#ifdef ALPINIST_GAME

#include "AlpinistMemento.h"
#include "Entities.h"
#include "Commands.h"

namespace AlpinistGame
{
	void AlpinistMemento::SetState(const std::vector<std::vector<TSharedPtr<Entity>>>& StateGrid)
	{
		m_grid = StateGrid;
	}

	void AlpinistCaretaker::Backup(AlpinistMemento*& NewMemento, PlayerCommand*& Command)
	{
		m_vectorMementos.push_back(std::make_pair(Command, NewMemento));
	}

	AlpinistMemento* AlpinistCaretaker::Undo(PlayerCommand*& Command)
	{
		const std::pair<PlayerCommand*, BaseMemento*> Pair = m_vectorMementos.back();
		if (Command != Pair.first)
			return nullptr;
		
		AlpinistMemento* Memento = dynamic_cast<AlpinistMemento*>(m_vectorMementos.back().second);
		m_vectorMementos.pop_back();
		
		return Memento;
	}

	std::vector<std::pair<AlpinistGame::PlayerDirection, std::pair<int8_t, int8_t>>> AlpinistCaretaker::GetPlayersHistory() const
	{
		std::vector<std::pair<AlpinistGame::PlayerDirection, std::pair<int8_t, int8_t>>> PlayersHistory = std::vector<std::pair<AlpinistGame::PlayerDirection, std::pair<int8_t, int8_t>>>();

		for (const auto& Memento : m_vectorMementos)
		{
			if (Memento.second)
			{
				for (const std::vector<TSharedPtr<Entity>>& Line : Memento.second->GetState())
				{
					bool bPlayerFound = false;
					for (const TSharedPtr<Entity>& Entity : Line)
					{
						if (const AlpinistGame::Player* Player = dynamic_cast<AlpinistGame::Player*>(Entity.Get()))
						{
							PlayersHistory.push_back(std::pair<AlpinistGame::PlayerDirection, std::pair<int8_t, int8_t>>(Player->GetDirection(), Player->GetPos()));
							bPlayerFound = true;
							break;
						}
					}
					if (bPlayerFound) break;
				}
			}
		}

		return PlayersHistory;
	}
}
#endif
