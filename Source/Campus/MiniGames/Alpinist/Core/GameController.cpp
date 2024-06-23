#include "GameController.h"
#include "Commands.h"

#ifdef ALPINIST_GAME
using namespace AlpinistGame;

GameController::GameController()
{
    std::vector<std::string> map  = {".......f",
                                        "........",
                                        "........",
                                        "p......."};
    m_world = new World(map);
}

GameController::GameController(const std::vector<std::string>& map)
{
    m_world = new World(map);
}

bool GameController::MoveForward()
{
    if (m_world)
    {
        const AlpinistGame::MoveResult result = m_world->SwapPlayerMove();
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

/*bool GameController::ExecuteMacroCommand(MacroCommand* macroCommand)
{
    return macroCommand->Execute();
}*/

#endif