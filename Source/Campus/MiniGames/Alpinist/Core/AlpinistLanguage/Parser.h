#pragma once

#include <string>
#include <stack>
#include "Token.h"

#ifdef ALPINIST_GAME

namespace AlpinistGame
{
	class Parser
	{
		std::stack<int8_t> StackScope;
		std::vector<TSharedPtr<Token>> Tokens;
		size_t Pos = 0;
		TWeakPtr<GameController> Controller;
		TSharedPtr<MacroCommand> CommandList;
		TSharedPtr<Creator> creator;
		
		TWeakPtr<AlpinistLog> Log = nullptr;
	public:
		Parser(const std::vector<TSharedPtr<Token>>& ListOfTokens, const TWeakPtr<GameController>& controller) : Tokens(ListOfTokens), Controller(controller)
		{
			CommandList = MakeShared<MacroCommand>();
			creator = MakeShared<Creator>();
		}
		~Parser();

		TSharedPtr<MacroCommand> SynAnalysis(TWeakPtr<AlpinistLog>& AlpLog);
	private:
		bool ContinueSynAnal(TWeakPtr<MacroCommand> commandList);

		bool AddSimpleCommand(const std::string& Command, TWeakPtr<MacroCommand> commandList);
		bool AddWhileLoop(const std::string& Command, TWeakPtr<MacroCommand> commandList);
		bool AddIfElseConditional(const std::string& Command, TWeakPtr<MacroCommand> commandList);

		template<typename CommandType>
		TSharedPtr<CommandType> CreateCommandWithCondition(const std::string& Command, TWeakPtr<MacroCommand> commandList, bool& CommandHasCondition);
		TSharedPtr<AlpinistGame::WhileCommand> CreateWhileCommandWithKeyword(const std::string& Command, TWeakPtr<MacroCommand> commandList, bool& CommandHasCondition);

		template<typename CommandType>
		bool FillScope(TSharedPtr<CommandType> Command, void(CommandType::* PushCommand)(const TSharedPtr<PlayerCommand>&), const bool HasCondition = true);
		bool FillCommandListScope(TWeakPtr<MacroCommand> macroCommandList);

		bool DeleteTokenFront();
		bool CheckStackScope();
		void SkipSpaceTokenIfThereItIs(Token* token);
		bool CheckKeywords();
	public:
		void GetNamesOfTokens() const;
	};

	template<typename CommandT>
	TSharedPtr<CommandT> Parser::CreateCommandWithCondition(const std::string& Command, TWeakPtr<MacroCommand> commandList, bool& CommandHasCondition)
	{
		bool NeedToBeNegate = false;
		Token* NegateToken = Tokens.front().Get();
		if (NegateToken->GetCommandType() == CT_Negate)
		{
			NeedToBeNegate = true;
			DeleteTokenFront();
		}

		Token* conditionToken = Tokens.front().Get();
		TSharedPtr<CommandT> instanceCommand = nullptr;
		if (conditionToken && conditionToken->GetCommandType() == CT_ConditionType)
		{
			if (const TSharedPtr<PlayerCommand> newConditionCommand = creator->Create(conditionToken->GetText(), Controller))
			{
				if (const TSharedPtr<ConditionCommand> condCommand = StaticCastSharedPtr<ConditionCommand>(newConditionCommand))
				{
					instanceCommand = StaticCastSharedPtr<CommandT>(creator->Create(Command, Controller, condCommand));
					if (instanceCommand)
					{
						commandList.Pin()->PushCommand(instanceCommand);
						DeleteTokenFront();
						CommandHasCondition = true;

						if (NeedToBeNegate)
						{
							condCommand->ToggleResult();
						}
					}
				}
			}
		}
		else if (conditionToken && conditionToken->GetCommandType() == CT_NotEnd)
		{
			Log.Pin()->PushMessageLog("Keyword \"NotEnd\" doesn't expect negating...", WarningMes);
		}
		else
		{
			const std::string What = Command;
			const std::string Exactly = " expects ConditionCommand...";
			const std::string WhatExactly = What + Exactly;
			
			Log.Pin()->PushMessageLog(WhatExactly, ErrorMes);
		}
		return instanceCommand;
	}

	template<typename CommandType>
	bool Parser::FillScope(TSharedPtr<CommandType> Command, void(CommandType::* PushCommand)(const TSharedPtr<PlayerCommand>&), const bool HasCondition)
	{
		Token* beginToken = Tokens.front().Get();
		const TSharedPtr<MacroCommand> macroElseCommandList = MakeShared<MacroCommand>();
		if (beginToken->GetCommandType() == CT_BeginScope && HasCondition)
		{
			if (!FillCommandListScope(macroElseCommandList.ToWeakPtr()))
			{
				return false;
			}
			for (TSharedPtr<PlayerCommand>& commandToAdd : macroElseCommandList->GetList())
			{
				(Command.Get()->*PushCommand)(commandToAdd);
			}
		}
		else
		{
			Log.Pin()->PushMessageLog("While/IfCommand hasn't Scope...", ErrorMes);
			return false;
		}
		return true;
	}
}

#endif