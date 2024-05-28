#include "GameController.h"
#include "Commands.h"
#include <iostream>

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
    const MoveResult result = m_world->SwapPlayerMove();
    return result == MoveResult::SUCCESS || result == MoveResult::FINISH;
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

bool GameController::WallInDirection(const Condition& condition)
{
    if(!m_world)
        return false;
    return m_world->WallInDirection(condition);
}

bool GameController::ExecuteMacroCommand(MacroCommand* macroCommand)
{
    return macroCommand->Execute();
} 