#include "GameController.h"
#include "Entities.h"
#include "AlpinistMemento.h"

#ifdef ALPINIST_GAME
using namespace AlpinistGame;

GameController::GameController()
{
    const std::vector<std::string> map  = {".......f",
                                        "........",
                                        "........",
                                        "p......."};
    m_world = new World(map);
    m_initialWorld = map;
    m_alpinistCaretaker = new AlpinistCaretaker();
}

GameController::GameController(const std::vector<std::string>& map)
{
    m_world = new World(map);
    m_initialWorld = map;
    m_alpinistCaretaker = new AlpinistCaretaker();
}

void GameController::SetNewMap(const std::vector<std::string>& map)
{
    if (m_world)
    {
        delete m_world;
    }
    m_world = new World(map);
    m_initialWorld = map;
}

bool GameController::MoveForward()
{
    if (m_world)
    {
        const AlpinistGame::MoveResult result = m_world->SwapPlayerMove();
        m_world->LogWorld();
        return result == AlpinistGame::MoveResult::MR_SUCCESS || result == AlpinistGame::MoveResult::MR_FINISH;
    }
    return false;
}

bool GameController::RotateRight()
{
    if(m_world)
    {
        if(Player* player = m_world->GetPlayer())
        {
            player->RotateRight();
            m_world->LogWorld();
            return true;
        }
    }
    return false;
}

bool GameController::RotateLeft()
{
    if(m_world)
    {
        if(Player* player = m_world->GetPlayer())
        {
            player->RotateLeft();
            m_world->LogWorld();
            return true;
        }
    }
    return false;
}

bool GameController::WallInDirection(const AlpinistGame::Condition& condition)
{
    if(!m_world)
        return false;
    
    return m_world->WallInDirection(condition);
}

bool GameController::PlayerNotOnFinish()
{
    if(!m_world)
        return false;
    
    return !m_world->IsPlayerFinished();
}

void GameController::ToStartPositions()
{
    m_world = new World(m_initialWorld);
    if (m_world)
    {
        m_world->LogWorld();
    }
}

bool GameController::SaveCopyOfWorld(PlayerCommand* Command)
{
    AlpinistMemento* NewMemento = new AlpinistMemento();
    if (NewMemento && m_world)
    {
        NewMemento->SetState(m_world->GetCopyOfGrid());

        if (m_alpinistCaretaker)
        {
            m_alpinistCaretaker->Backup(NewMemento, Command);
            return true;
        }
    }
    return false;
}

bool GameController::RestoreOfWorld(PlayerCommand* Command)
{
    if (m_alpinistCaretaker)
    {
        if (AlpinistMemento* Memento = m_alpinistCaretaker->Undo(Command))
        {
            if (m_world)
            {
                m_world->SetGrid(Memento->GetState());
                return true;
            }
        }
    }
    return false;
}

/*bool GameController::ExecuteMacroCommand(MacroCommand* macroCommand)
{
    return macroCommand->Execute();
}*/

#endif