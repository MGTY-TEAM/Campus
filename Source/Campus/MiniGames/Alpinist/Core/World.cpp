#include "World.h"

#ifdef ALPINIST_GAME
using namespace AlpinistGame;

bool World::IsValidPosition(std::pair<int8_t, int8_t> position) const
{
	if (m_grid.empty())
		return false;

	return (position.first >= 0 && position.first < m_grid.size() && position.second >= 0 && position.second < m_grid[
		position.first].size());
}

World::World(const std::vector<std::string>& grid)
{
	m_grid.resize(grid.size(), std::vector<Entity*>());
	for (size_t i = 0; i < grid.size(); ++i)
	{
		m_grid[i].resize(grid[i].size(), nullptr);
		for (size_t j = 0; j < grid[i].size(); ++j)
		{
			switch (grid[i][j])
			{
			case('.'):
				m_grid[i][j] = nullptr;
				break;
			case('p'):
				m_player = new Player(std::make_pair(i, j), PlayerDirection::UP); // TO DO: DIRECTION FIX
				m_grid[i][j] = m_player;
				break;
			case('w'):
				m_grid[i][j] = new Wall(std::make_pair(i, j));
				break;
			case('f'):
				m_grid[i][j] = new Finish(std::make_pair(i, j));
				break;
			default: break;
			}
		}
	}
}

MoveResult World::SwapPlayerMove()
{
	if (m_grid.empty() || !m_player)
		return ERROR;

	std::pair<int8_t, int8_t> direction = GetDirectionFromByteCode(m_player->GetDirection());
	std::pair<int8_t, int8_t> position = m_player->GetPos();
	std::pair<int8_t, int8_t> nextPosition = std::make_pair(direction.first + position.first,
	                                                        direction.second + position.second);

	if (IsValidPosition(nextPosition))
	{
		Entity* entity = m_grid[nextPosition.first][nextPosition.second];

		if (!entity)
		{
			m_grid[nextPosition.first][nextPosition.second] = m_player;
			m_grid[position.first][position.second] = nullptr;
			m_player->SetPos(nextPosition);
			return SUCCESS;
		}
		else if (Finish* finish = dynamic_cast<Finish*>(entity))
		{
			/////////////////////////////////////////////////////////TO DO:
			m_grid[nextPosition.first][nextPosition.second] = m_player;
			m_grid[position.first][position.second] = nullptr;
			m_player->SetPos(nextPosition);
			
			bFinished = true;
			
			return FINISH;
		}
	}
	return ERROR;
}

bool World::WallInDirection(const Condition& condition)
{
	if (m_grid.empty() || !m_player)
		return false;

	PlayerDirection playerDirection = m_player->GetDirection();
	std::pair<int8_t, int8_t> direction = GetDirectionFromByteCode(playerDirection);
	std::pair<int8_t, int8_t> checkedCellPos;
	switch (condition)
	{
	case WALL_RIGHT:
		direction = GetDirectionFromByteCode(++playerDirection);
		break;
	case WALL_LEFT:
		direction = GetDirectionFromByteCode(--playerDirection);
		break;
	default:
		break;
	}
	checkedCellPos = std::make_pair(m_player->GetPos().first + direction.first,
	                                m_player->GetPos().second + direction.second);
	if (IsValidPosition(checkedCellPos))
	{
		if (Wall* wall = dynamic_cast<Wall*>(m_grid[checkedCellPos.first][checkedCellPos.second]))
		{
			return true;
		}
	}
	return false;
}

std::ostream& AlpinistGame::operator<<(std::ostream& os, World* world)
{
	if (world->m_grid.empty())
		return os;

	for (size_t i = 0; i < world->m_grid.size(); ++i)
	{
		for (size_t j = 0; j < world->m_grid[i].size(); ++j)
		{
			if (world->m_grid[i][j])
			{
				if (dynamic_cast<Player*>(world->m_grid[i][j]))
				{
					os << "p";
				}
				else if (dynamic_cast<Wall*>(world->m_grid[i][j]))
				{
					os << "w";
				}
				else if (dynamic_cast<Finish*>(world->m_grid[i][j]))
				{
					os << "f";
				}
			}
			else
			{
				os << ".";
			}
		}
		os << "\n";
	}
	return os;
}
#endif
