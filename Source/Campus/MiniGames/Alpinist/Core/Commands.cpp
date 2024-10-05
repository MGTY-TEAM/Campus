#ifdef ALPINIST_GAME

#include "Commands.h"
//#include "GameController.h"

using namespace AlpinistGame;

bool RotateRightCommand::Execute(AlpinistGame::AlpinistLog* AlpLog)
{
	if (!m_gameController)
		return false;

	m_gameController->SaveCopyOfWorld(this);
	return m_gameController->RotateRight();
}

bool RotateRightCommand::Unexecute()
{
	if (!m_gameController)
		return false;

	return m_gameController->RestoreOfWorld(this);
}

bool RotateLeftCommand::Execute(AlpinistGame::AlpinistLog* AlpLog)
{
	if (!m_gameController)
		return false;

	m_gameController->SaveCopyOfWorld(this);
	return m_gameController->RotateLeft();
}

bool RotateLeftCommand::Unexecute()
{
	if (!m_gameController)
		return false;

	return m_gameController->RestoreOfWorld(this);
}

bool MoveCommand::Execute(AlpinistGame::AlpinistLog* AlpLog)
{
	if (!m_gameController)
		return false;
	
	m_gameController->SaveCopyOfWorld(this);
	return m_gameController->MoveForward();
}

bool MoveCommand::Unexecute()
{
	if (!m_gameController)
		return false;

	return m_gameController->RestoreOfWorld(this);
}

bool MacroCommand::Execute(AlpinistGame::AlpinistLog* AlpLog)
{
	for (PlayerCommand* playerCommand : m_commandList)
	{
		if (!playerCommand->Execute(AlpLog))
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

bool ConditionCommand::Execute(AlpinistGame::AlpinistLog* AlpLog)
{
	if (!m_gameController)
		return false;

	m_bResult = m_gameController->WallInDirection(m_definition);
	return true;
}

bool NotEndCommand::Execute(AlpinistGame::AlpinistLog* AlpLog)
{
	if (!m_gameController)
		return false;

	m_bResult = m_gameController->PlayerNotOnFinish();
	return true;
}

bool IfCommand::Execute(AlpinistGame::AlpinistLog* AlpLog)
{
	if (!m_conditionCommand) return false;
	m_conditionCommand->Execute(AlpLog);
	if (m_conditionCommand->GetResult())
	{
		for (PlayerCommand* playerCommand : m_commandListIfTrue)
		{
			if (!playerCommand->Execute(AlpLog))
				return false;
		}
	}
	else
	{
		for (PlayerCommand* playerCommand : m_commandListIfFalse)
		{
			if (!playerCommand->Execute(AlpLog))
				return false;
		}
	}
	return true;
}
#endif