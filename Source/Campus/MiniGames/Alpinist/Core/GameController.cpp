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
    m_world = MakeShared<World>(map);
    m_initialWorld = map;
    m_alpinistCaretaker = MakeShared<AlpinistCaretaker>();
}

GameController::GameController(const std::vector<std::string>& map)
{
    m_world = MakeShared<World>(map);
    m_initialWorld = map;
    m_alpinistCaretaker = MakeShared<AlpinistCaretaker>();
}

void GameController::SetNewMap(const std::vector<std::string>& map)
{
    if (m_world.Get())
    {
        m_world.Reset();
    }
    m_world = MakeShared<World>(map);
    m_initialWorld = map;
}

bool GameController::MoveForward()
{
    if (m_world.Get())
    {
        const AlpinistGame::MoveResult result = m_world->SwapPlayerMove();
        m_world->LogWorld();
        
        if (result == AlpinistGame::MoveResult::MR_SUCCESS || result == AlpinistGame::MoveResult::MR_FINISH)
        {
            return true;
        }
    }
    return false;
}

bool GameController::RotateRight()
{
    if(m_world.Get())
    {
        if(Player* player = m_world->GetPlayer().Get())
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
    if(m_world.Get())
    {
        if(Player* player = m_world->GetPlayer().Get())
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
    if(!m_world.Get())
        return false;
    
    return m_world->WallInDirection(condition);
}

bool GameController::PlayerNotOnFinish()
{
    if(!m_world.Get())
        return false;
    
    return !m_world->IsPlayerFinished();
}

void GameController::ToStartPositions()
{
    m_world = MakeShared<World>(m_initialWorld);
    if (m_world.Get())
    {
        m_world->LogWorld();
    }
}

bool GameController::SaveCopyOfWorld(PlayerCommand* Command)
{
    AlpinistMemento* NewMemento = new AlpinistMemento();
    if (NewMemento && m_world.Get())
    {
        NewMemento->SetState(m_world->GetCopyOfGrid());

        if (m_alpinistCaretaker.Get())
        {
            m_alpinistCaretaker->Backup(NewMemento, Command);
            return true;
        }
    }
    return false;
}

bool GameController::RestoreOfWorld(PlayerCommand* Command)
{
    if (m_alpinistCaretaker.Get())
    {
        if (AlpinistMemento* Memento = m_alpinistCaretaker->Undo(Command))
        {
            if (m_world.Get())
            {
                m_world->SetGrid(Memento->GetState());
                return true;
            }
        }
    }
    return false;
}

void GameController::ClearHistory()
{
    if (m_alpinistCaretaker.IsValid())
    {
        m_alpinistCaretaker->ClearHistory();
    }
}

/*bool GameController::ExecuteMacroCommand(MacroCommand* macroCommand)
{
    return macroCommand->Execute();
}*/

#endif