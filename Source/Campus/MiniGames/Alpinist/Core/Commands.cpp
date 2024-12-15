#ifdef ALPINIST_GAME

#include "Commands.h"
//#include "GameController.h"

using namespace AlpinistGame;

bool RotateRightCommand::Execute(TWeakPtr<AlpinistGame::AlpinistLog>& AlpLog)
{
	if (!m_gameController.IsValid())
		return false;

	m_gameController.Pin()->SaveCopyOfWorld(this);
	return m_gameController.Pin()->RotateRight();
}

bool RotateRightCommand::Unexecute()
{
	if (!m_gameController.IsValid())
		return false;

	return m_gameController.Pin()->RestoreOfWorld(this);
}

bool RotateLeftCommand::Execute(TWeakPtr<AlpinistGame::AlpinistLog>& AlpLog)
{
	if (!m_gameController.IsValid())
		return false;

	m_gameController.Pin()->SaveCopyOfWorld(this);
	return m_gameController.Pin()->RotateLeft();
}

bool RotateLeftCommand::Unexecute()
{
	if (!m_gameController.IsValid())
		return false;

	return m_gameController.Pin()->RestoreOfWorld(this);
}

bool MoveCommand::Execute(TWeakPtr<AlpinistGame::AlpinistLog>& AlpLog)
{
	if (!m_gameController.IsValid())
		return false;
	
	m_gameController.Pin()->SaveCopyOfWorld(this);
	return m_gameController.Pin()->MoveForward();
}

bool MoveCommand::Unexecute()
{
	if (!m_gameController.IsValid())
		return false;

	return m_gameController.Pin()->RestoreOfWorld(this);
}

bool MacroCommand::Execute(TWeakPtr<AlpinistGame::AlpinistLog>& AlpLog)
{
	for (TSharedPtr<PlayerCommand>& playerCommand : m_commandList)
	{
		if (!playerCommand->Execute(AlpLog))
			return false;
	}
	return true;
}

void MacroCommand::PushCommand(const TSharedPtr<PlayerCommand>& playerCommand)
{
	m_commandList.push_back(playerCommand);
}

void ConditionCommand::ToggleResult()
{
	m_shouldBeNegation = !m_shouldBeNegation;
}

bool ConditionCommand::Execute(TWeakPtr<AlpinistGame::AlpinistLog>& AlpLog)
{
	if (!m_gameController.IsValid())
		return false;

	m_bResult = m_gameController.Pin()->WallInDirection(m_definition);
	return true;
}

bool NotEndCommand::Execute(TWeakPtr<AlpinistGame::AlpinistLog>& AlpLog)
{
	if (!m_gameController.IsValid())
		return false;

	m_bResult = m_gameController.Pin()->PlayerNotOnFinish();
	return true;
}

bool IfCommand::Execute(TWeakPtr<AlpinistGame::AlpinistLog>& AlpLog)
{
	if (!m_conditionCommand.IsValid()) return false;
	m_conditionCommand->Execute(AlpLog);
	if (m_conditionCommand->GetResult())
	{
		for (TSharedPtr<PlayerCommand>& playerCommand : m_commandListIfTrue)
		{
			if (!playerCommand->Execute(AlpLog))
				return false;
		}
	}
	else
	{
		for (TSharedPtr<PlayerCommand>& playerCommand : m_commandListIfFalse)
		{
			if (!playerCommand->Execute(AlpLog))
				return false;
		}
	}
	return true;
}
#endif