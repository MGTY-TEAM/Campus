#pragma once
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
		}
	};

	class RotateRightCommand : public PlayerCommand
	{
		GameController* m_gameController;

	public:
		RotateRightCommand(GameController* gameController) : m_gameController(gameController)
		{
		}

		bool Execute() override;
	};

	class RotateLeftCommand : public PlayerCommand
	{
		GameController* m_gameController;

	public:
		RotateLeftCommand(GameController* gameController) : m_gameController(gameController)
		{
		}

		bool Execute() override;
	};

	class MoveCommand : public PlayerCommand
	{
		GameController* m_gameController;

	public:
		MoveCommand(GameController* gameController) : m_gameController(gameController)
		{
		}

		bool Execute() override;
	};

	class MacroCommand : public PlayerCommand
	{
	protected:
		std::list<PlayerCommand*> m_commandList;

	public:
		MacroCommand()
		{
		}

		bool Execute() override;

		void PushCommand(PlayerCommand* playerCommand);
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

		bool GetResult() const;
		void ToggleResult();

		bool Execute() override;

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

		bool m_bConditon;

	public:
		IfCommand()
		{
		}

		IfCommand(bool Condition) : m_bConditon(Condition)
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

		void SetCondition(bool Condition) { m_bConditon = Condition; }

		bool Execute() override;
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
}
