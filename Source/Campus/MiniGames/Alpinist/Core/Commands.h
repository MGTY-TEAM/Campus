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

		virtual bool Execute(TWeakPtr<AlpinistGame::AlpinistLog>& AlpLog)
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
		TWeakPtr<GameController> m_gameController;

	public:
		RotateRightCommand(const TWeakPtr<GameController>& gameController) : m_gameController(gameController)
		{
		}

		virtual bool Execute(TWeakPtr<AlpinistGame::AlpinistLog>& AlpLog) override;
		virtual bool Unexecute() override;
	};

	class RotateLeftCommand : public PlayerCommand
	{
		TWeakPtr<GameController> m_gameController;

	public:
		RotateLeftCommand(const TWeakPtr<GameController>& gameController) : m_gameController(gameController)
		{
		}

		virtual bool Execute(TWeakPtr<AlpinistGame::AlpinistLog>& AlpLog) override;
		virtual bool Unexecute() override;
	};

	class MoveCommand : public PlayerCommand
	{
		TWeakPtr<GameController> m_gameController;

	public:
		MoveCommand(const TWeakPtr<GameController>& gameController) : m_gameController(gameController)
		{
		}

		virtual bool Execute(TWeakPtr<AlpinistGame::AlpinistLog>& AlpLog) override;
		virtual bool Unexecute() override;
	};

	class MacroCommand : public PlayerCommand
	{
	protected:
		std::list<TSharedPtr<PlayerCommand>> m_commandList;

	public:
		MacroCommand()
		{
		}

		virtual bool Execute(TWeakPtr<AlpinistGame::AlpinistLog>& AlpLog) override;

		void PushCommand(const TSharedPtr<PlayerCommand>& playerCommand);

		std::list<TSharedPtr<PlayerCommand>> GetList() const { return m_commandList; }
	};

	class ConditionCommand : public PlayerCommand
	{
		TWeakPtr<GameController> m_gameController;

		Condition m_definition;

		bool m_bResult = false;
		bool m_shouldBeNegation = false;

	public:
		ConditionCommand(const TWeakPtr<GameController>& gameController, Condition definition) : m_gameController(gameController),
			m_definition(definition)
		{
		}

		bool GetResult() const { return m_shouldBeNegation ? !m_bResult : m_bResult; }
		void ToggleResult();

		virtual bool Execute(TWeakPtr<AlpinistGame::AlpinistLog>& AlpLog) override;

		TSharedPtr<ConditionCommand> operator!()
		{
			TSharedPtr<ConditionCommand> NewCommand = MakeShared<ConditionCommand>(this->m_gameController, this->m_definition);
			NewCommand->ToggleResult();

			return NewCommand;
		}
	};

	class NotEndCommand : public PlayerCommand
	{
		TWeakPtr<GameController> m_gameController;
		bool m_bResult = false;

	public:
		NotEndCommand(const TWeakPtr<GameController>& gameController) : m_gameController(gameController)
		{
		}

		bool GetResult() const { return m_bResult; }
		
		virtual bool Execute(TWeakPtr<AlpinistGame::AlpinistLog>& AlpLog) override;
	};
	
	class IfCommand : public PlayerCommand
	{
		std::list<TSharedPtr<PlayerCommand>> m_commandListIfTrue;
		std::list<TSharedPtr<PlayerCommand>> m_commandListIfFalse;

		TSharedPtr<ConditionCommand> m_conditionCommand;

	public:
		IfCommand()
		{
		}

		IfCommand(const TSharedPtr<ConditionCommand>& ConditionCommand) : m_conditionCommand(ConditionCommand)
		{
		}

		void PushCommandInTrueIf(const TSharedPtr<PlayerCommand>& playerCommand)
		{
			m_commandListIfTrue.push_back(playerCommand);
		}

		void PushCommandInFalseIf(const TSharedPtr<PlayerCommand>& playerCommand)
		{
			m_commandListIfFalse.push_back(playerCommand);
		}

		// void SetCondition(bool Condition) { m_bConditon = Condition; }

		virtual bool Execute(TWeakPtr<AlpinistGame::AlpinistLog>& AlpLog) override;
	};
	
	class WhileCommand : public MacroCommand
	{
		TSharedPtr<ConditionCommand> m_conditionCommand;
		TSharedPtr<NotEndCommand> m_notEndCommand;

		size_t CountOfExecution = 0;
	public:
		WhileCommand() {}

		WhileCommand(const TSharedPtr<ConditionCommand>& conditionCommand) : m_conditionCommand(conditionCommand)
		{
			m_notEndCommand = nullptr;
		}
		WhileCommand(const TSharedPtr<NotEndCommand>& notEndCommand) : m_notEndCommand(notEndCommand)
		{
			m_conditionCommand = nullptr;
		}

		virtual bool Execute(TWeakPtr<AlpinistGame::AlpinistLog>& AlpLog) override
		{
			if (m_conditionCommand.IsValid())
			{
				return ExecuteCondition(m_conditionCommand, &ConditionCommand::Execute, AlpLog, &ConditionCommand::GetResult);
			}
			if (m_notEndCommand.IsValid())
			{
				return ExecuteCondition(m_notEndCommand, &NotEndCommand::Execute, AlpLog, &NotEndCommand::GetResult);
			} 
			return false;
		}

	private:
		template<typename TypeOfConditionCommand>
		bool ExecuteCondition(const TSharedPtr<TypeOfConditionCommand>& Command, bool(TypeOfConditionCommand::* Execute)(TWeakPtr<AlpinistGame::AlpinistLog>&), TWeakPtr<AlpinistGame::AlpinistLog> AlpLog, bool(TypeOfConditionCommand::* GetResult)() const);
	};

	template <typename TypeOfConditionCommand>
	bool WhileCommand::ExecuteCondition(const TSharedPtr<TypeOfConditionCommand>& Command, bool(TypeOfConditionCommand::* Execute)(TWeakPtr<AlpinistGame::AlpinistLog>&), TWeakPtr<AlpinistGame::AlpinistLog> AlpLog, bool(TypeOfConditionCommand::* GetResult)() const)
	{
		if (Command.IsValid())
		{
			(Command.Get()->*Execute)(AlpLog);
			while ((Command.Get()->*GetResult)())
			{
				for (TSharedPtr<PlayerCommand>& playerCommand : m_commandList)
				{
					if (!playerCommand->Execute(AlpLog))
						return false;
				}
				(Command.Get()->*Execute)(AlpLog);

				if (CountOfExecution++ == 100)
				{
					if (AlpLog.IsValid())
					{
						AlpLog.Pin()->PushMessageLog("Warning: Infinite Circle in WhileLoop...", AlpinistGame::WarningMes);
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
		virtual TSharedPtr<PlayerCommand> Create(std::string Command, TWeakPtr<GameController> controller, TSharedPtr<ConditionCommand> conditionCommand = nullptr)
		{
			if (Command == "move") return MakeShared<MoveCommand>(controller);
			if (Command == "right") return MakeShared<RotateRightCommand>(controller);
			if (Command == "left") return MakeShared<RotateLeftCommand>(controller);
			if (Command == "wallAhead") return MakeShared<ConditionCommand>(controller, C_WALL_FORWARD);
			if (Command == "wallRight") return MakeShared<ConditionCommand>(controller, C_WALL_RIGHT);
			if (Command == "wallLeft") return MakeShared<ConditionCommand>(controller, C_WALL_LEFT);
			if (Command == "while") return MakeShared<WhileCommand>(conditionCommand);
			if (Command == "if") return MakeShared<IfCommand>(conditionCommand);
			if (Command == "NotEnd") return MakeShared<NotEndCommand>(controller);

			return nullptr;
		}
		virtual TSharedPtr<PlayerCommand> CreateWhileNotEnd(std::string Command, TWeakPtr<GameController> controller, TSharedPtr<NotEndCommand> notEndCommand = nullptr)
		{
			if (Command == "while" && notEndCommand.IsValid()) return MakeShared<WhileCommand>(notEndCommand);

			return nullptr;
		}
	};
}
#endif