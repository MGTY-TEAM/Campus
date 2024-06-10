#pragma once

#include "GameController.h"
#ifdef ALPINIST_GAME

#include "GameTypes.h"

namespace AlpinistGame
{
	class GameController;

	class PlayerCommand
	{
	protected:
		PlayerCommand()
		{
		}

	public:
		virtual ~PlayerCommand()
		{
		}

		virtual bool Execute()
		{
			return false;
		}
	};

	class RotateRightCommand : public PlayerCommand
	{
		GameController* m_gameController;

	public:
		RotateRightCommand(GameController* gameController) : m_gameController(gameController)
		{
		}

		virtual bool Execute() override;
	};

	class RotateLeftCommand : public PlayerCommand
	{
		GameController* m_gameController;

	public:
		RotateLeftCommand(GameController* gameController) : m_gameController(gameController)
		{
		}

		virtual bool Execute() override;
	};

	class MoveCommand : public PlayerCommand
	{
		GameController* m_gameController;

	public:
		MoveCommand(GameController* gameController) : m_gameController(gameController)
		{
		}

		virtual bool Execute() override;
	};

	class MacroCommand : public PlayerCommand
	{
	protected:
		std::list<PlayerCommand*> m_commandList;

	public:
		MacroCommand()
		{
		}

		virtual bool Execute() override;

		void PushCommand(PlayerCommand* playerCommand);

		std::list<PlayerCommand*> GetList() const { return m_commandList; }
	};

	class ConditionCommand : public PlayerCommand
	{
		GameController* m_gameController;

		Condition m_definition;

		bool m_bResult;
		bool m_shouldBeNegation = false;

	public:
		ConditionCommand(GameController* gameController, Condition definition) : m_gameController(gameController),
			m_definition(definition)
		{
		}

		bool GetResult() const { return m_shouldBeNegation ? !m_bResult : m_bResult; }
		void ToggleResult();

		virtual bool Execute() override;

		ConditionCommand* operator!()
		{
			ConditionCommand* NewCommand = new ConditionCommand(this->m_gameController, this->m_definition);
			NewCommand->ToggleResult();

			return NewCommand;
		}
	};

	class IfCommand : public PlayerCommand
	{
		std::list<PlayerCommand*> m_commandListIfTrue;
		std::list<PlayerCommand*> m_commandListIfFalse;

		ConditionCommand* m_conditionCommand;

	public:
		IfCommand()
		{
		}

		IfCommand(ConditionCommand* ConditionCommand) : m_conditionCommand(ConditionCommand)
		{
		}

		void PushCommandInTrueIf(PlayerCommand* playerCommand)
		{
			m_commandListIfTrue.push_back(playerCommand);
			
		}

		void PushCommandInFalseIf(PlayerCommand* playerCommand)
		{
			m_commandListIfFalse.push_back(playerCommand);
		}

		// void SetCondition(bool Condition) { m_bConditon = Condition; }

		virtual bool Execute() override;
	};

	class WhileCommand : public MacroCommand
	{
		ConditionCommand* m_conditionCommand;

	public:
		WhileCommand()
		{
		}

		WhileCommand(ConditionCommand* ConditionCommand) : m_conditionCommand(ConditionCommand)
		{
		}

		void SetConditionCommand(ConditionCommand* ConditionCommand) { m_conditionCommand = ConditionCommand; }

		virtual bool Execute() override
		{
			m_conditionCommand->Execute();
			while (m_conditionCommand->GetResult())
			{
				for (PlayerCommand* playerCommand : m_commandList)
				{
					if (!playerCommand->Execute())
						return false;
				}
				m_conditionCommand->Execute();
			}
			return true;
		}
	};

	class Creator
	{
	public:
		virtual PlayerCommand* Create(std::string Command, GameController* controller, ConditionCommand* conditionCommand = nullptr)
		{
			if (Command == "move") return new MoveCommand(controller);
			if (Command == "right") return new RotateRightCommand(controller);
			if (Command == "left") return new RotateLeftCommand(controller);
			if (Command == "wallAhead") return new ConditionCommand(controller, WALL_FORWARD);
			if (Command == "wallRight") return new ConditionCommand(controller, WALL_RIGHT);
			if (Command == "wallLeft") return new ConditionCommand(controller, WALL_LEFT);
			if (Command == "while") return new WhileCommand(conditionCommand);
			if (Command == "if") return new IfCommand(conditionCommand);

			return nullptr;
		}
	};
}
#endif