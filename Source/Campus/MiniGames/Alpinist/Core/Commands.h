#pragma once

#ifdef ALPINIST_GAME

#include "GameTypes.h"
#include "GameController.h"

namespace AlpinistGame
{
	class AlpinistLog;
}


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

		virtual bool Execute(AlpinistGame::AlpinistLog* AlpLog)
		{
			return false;
		}
		virtual bool Unexecute()
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

		virtual bool Execute(AlpinistGame::AlpinistLog* AlpLog) override;
		virtual bool Unexecute() override;
	};

	class RotateLeftCommand : public PlayerCommand
	{
		GameController* m_gameController;

	public:
		RotateLeftCommand(GameController* gameController) : m_gameController(gameController)
		{
		}

		virtual bool Execute(AlpinistGame::AlpinistLog* AlpLog) override;
		virtual bool Unexecute() override;
	};

	class MoveCommand : public PlayerCommand
	{
		GameController* m_gameController;

	public:
		MoveCommand(GameController* gameController) : m_gameController(gameController)
		{
		}

		virtual bool Execute(AlpinistGame::AlpinistLog* AlpLog) override;
		virtual bool Unexecute() override;
	};

	class MacroCommand : public PlayerCommand
	{
	protected:
		std::list<PlayerCommand*> m_commandList;

	public:
		MacroCommand()
		{
		}

		virtual bool Execute(AlpinistGame::AlpinistLog* AlpLog) override;

		void PushCommand(PlayerCommand* playerCommand);

		std::list<PlayerCommand*> GetList() const { return m_commandList; }
	};

	class ConditionCommand : public PlayerCommand
	{
		GameController* m_gameController;

		Condition m_definition;

		bool m_bResult = false;
		bool m_shouldBeNegation = false;

	public:
		ConditionCommand(GameController* gameController, Condition definition) : m_gameController(gameController),
			m_definition(definition)
		{
		}

		bool GetResult() const { return m_shouldBeNegation ? !m_bResult : m_bResult; }
		void ToggleResult();

		virtual bool Execute(AlpinistGame::AlpinistLog* AlpLog) override;

		ConditionCommand* operator!()
		{
			ConditionCommand* NewCommand = new ConditionCommand(this->m_gameController, this->m_definition);
			NewCommand->ToggleResult();

			return NewCommand;
		}
	};

	class NotEndCommand : public PlayerCommand
	{
		GameController* m_gameController;
		bool m_bResult = false;

	public:
		NotEndCommand(GameController* gameController) : m_gameController(gameController)
		{
		}

		bool GetResult() const { return m_bResult; }
		
		virtual bool Execute(AlpinistGame::AlpinistLog* AlpLog) override;
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

		virtual bool Execute(AlpinistGame::AlpinistLog* AlpLog) override;
	};
	
	class WhileCommand : public MacroCommand
	{
		ConditionCommand* m_conditionCommand;
		NotEndCommand* m_notEndCommand;

		size_t CountOfExecution = 0;
	public:
		WhileCommand() {}

		WhileCommand(ConditionCommand* conditionCommand) : m_conditionCommand(conditionCommand)
		{
			m_notEndCommand = nullptr;
		}
		WhileCommand(NotEndCommand* notEndCommand) : m_notEndCommand(notEndCommand)
		{
			m_conditionCommand = nullptr;
		}

		virtual bool Execute(AlpinistGame::AlpinistLog* AlpLog) override
		{
			if (m_conditionCommand)
			{
				return ExecuteCondition(m_conditionCommand, &ConditionCommand::Execute, AlpLog, &ConditionCommand::GetResult);
			}
			if (m_notEndCommand)
			{
				return ExecuteCondition(m_notEndCommand, &NotEndCommand::Execute, AlpLog, &NotEndCommand::GetResult);
			} 
			return false;
		}

	private:
		template<typename TypeOfConditionCommand>
		bool ExecuteCondition(TypeOfConditionCommand* Command, bool(TypeOfConditionCommand::* Execute)(AlpinistGame::AlpinistLog*), AlpinistGame::AlpinistLog* AlpLog, bool(TypeOfConditionCommand::* GetResult)() const);
	};

	template <typename TypeOfConditionCommand>
	bool WhileCommand::ExecuteCondition(TypeOfConditionCommand* Command, bool(TypeOfConditionCommand::* Execute)(AlpinistGame::AlpinistLog*), AlpinistGame::AlpinistLog* AlpLog, bool(TypeOfConditionCommand::* GetResult)() const)
	{
		if (Command)
		{
			(Command->*Execute)(AlpLog);
			while ((Command->*GetResult)())
			{
				for (PlayerCommand* playerCommand : m_commandList)
				{
					if (!playerCommand->Execute(AlpLog))
						return false;
				}
				(Command->*Execute)(AlpLog);

				if (CountOfExecution++ == 100)
				{
					if (AlpLog)
					{
						AlpLog->PushMessageLog("Warning: Infinite Circle in WhileLoop...", AlpinistGame::WarningMes);
					}
					return false;
				}
			}
				
			return true;
		}
		return false;
	}

	class Creator
	{
	public:
		virtual PlayerCommand* Create(std::string Command, GameController* controller, ConditionCommand* conditionCommand = nullptr)
		{
			if (Command == "move") return new MoveCommand(controller);
			if (Command == "right") return new RotateRightCommand(controller);
			if (Command == "left") return new RotateLeftCommand(controller);
			if (Command == "wallAhead") return new ConditionCommand(controller, C_WALL_FORWARD);
			if (Command == "wallRight") return new ConditionCommand(controller, C_WALL_RIGHT);
			if (Command == "wallLeft") return new ConditionCommand(controller, C_WALL_LEFT);
			if (Command == "while") return new WhileCommand(conditionCommand);
			if (Command == "if") return new IfCommand(conditionCommand);
			if (Command == "NotEnd") return new NotEndCommand(controller);

			return nullptr;
		}
		virtual PlayerCommand* CreateWhileNotEnd(std::string Command, GameController* controller, NotEndCommand* notEndCommand = nullptr)
		{
			if (Command == "while" && notEndCommand) return new WhileCommand(notEndCommand);

			return nullptr;
		}
	};
}
#endif