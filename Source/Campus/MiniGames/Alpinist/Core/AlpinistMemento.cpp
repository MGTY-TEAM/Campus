
#ifdef ALPINIST_GAME

#include "AlpinistMemento.h"
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
}
#endif
