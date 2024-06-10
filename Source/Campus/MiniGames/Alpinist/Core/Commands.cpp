#include "Commands.h"
#include "GameController.h"

#ifdef ALPINIST_GAME
using namespace AlpinistGame;

bool RotateRightCommand::Execute()
{
	if (!m_gameController)
		return false;
	return m_gameController->RotateRight();
}

bool RotateLeftCommand::Execute()
{
	if (!m_gameController)
		return false;
	return m_gameController->RotateLeft();
}

bool MoveCommand::Execute()
{
	if (!m_gameController)
		return false;
	return m_gameController->MoveForward();
}

bool MacroCommand::Execute()
{
	for (PlayerCommand* playerCommand : m_commandList)
	{
		if (!playerCommand->Execute())
			return false;
	}
	return true;
}

void MacroCommand::PushCommand(PlayerCommand* playerCommand)
{
	m_commandList.push_back(playerCommand);
}

void ConditionCommand::ToggleResult()
{
	m_shouldBeNegation = !m_shouldBeNegation;
}

bool ConditionCommand::Execute()
{
	if (!m_gameController)
		return false;

	m_bResult = m_gameController->WallInDirection(m_definition);
	return true;
}

bool IfCommand::Execute()
{
	if (!m_conditionCommand) return false;
	m_conditionCommand->Execute();
	if (m_conditionCommand->GetResult())
	{
		for (PlayerCommand* playerCommand : m_commandListIfTrue)
		{
			if (!playerCommand->Execute())
				return false;
		}
	}
	else
	{
		for (PlayerCommand* playerCommand : m_commandListIfFalse)
		{
			if (!playerCommand->Execute())
				return false;
		}
	}
	return true;
}
#endif