#pragma once

#include <string>
#include <stack>
#include "Token.h"
// #include "../Commands.h"
// #include "../GameController.h"
#ifdef ALPINIST_GAME
namespace AlpinistGame
{
	class Parser
	{
		std::stack<int8_t> StackScope;
		std::vector<TSharedPtr<Token>> Tokens;
		size_t Pos = 0;
		GameController* Controller;
		TSharedPtr<MacroCommand> CommandList;
		TSharedPtr<Creator> creator;

		AlpinistLog* Log = nullptr;
	public:
		Parser(const std::vector<TSharedPtr<Token>>& ListOfTokens, GameController* controller) : Tokens(ListOfTokens), Controller(controller)
		{
			CommandList = MakeShared<MacroCommand>();
			creator = MakeShared<Creator>();
		}
		~Parser();

		TSharedPtr<MacroCommand> SynAnalysis(AlpinistLog& AlpLog);
	private:
		bool ContinueSynAnal(MacroCommand* commandList);

		bool AddSimpleCommand(const std::string& Command, MacroCommand* commandList);
		bool AddWhileLoop(const std::string& Command, MacroCommand* commandList);
		bool AddIfElseConditional(const std::string& Command, MacroCommand* commandList);

		template<typename CommandType>
		CommandType* CreateCommandWithCondition(const std::string& Command, MacroCommand* commandList, bool& CommandHasCondition);
		WhileCommand* CreateWhileCommandWithKeyword(const std::string& Command, MacroCommand* commandList, bool& CommandHasCondition);

		template<typename CommandType>
		bool FillScope(CommandType* Command, void(CommandType::* PushCommand)(PlayerCommand*), const bool HasCondition = true);
		bool FillCommandListScope(MacroCommand* macroCommandList);

		bool DeleteTokenFront();
		bool CheckStackScope();
		void SkipSpaceTokenIfThereItIs(Token* token);
		bool CheckKeywords();
	public:
		void GetNamesOfTokens() const;
	};

	template<typename CommandT>
	CommandT* Parser::CreateCommandWithCondition(const std::string& Command, MacroCommand* commandList, bool& CommandHasCondition)
	{
		bool NeedToBeNegate = false;
		Token* NegateToken = Tokens.front().Get();
		if (NegateToken->GetCommandType() == CT_Negate)
		{
			NeedToBeNegate = true;
			DeleteTokenFront();
		}

		Token* conditionToken = Tokens.front().Get();
		CommandT* instanceCommand = nullptr;
		if (conditionToken && conditionToken->GetCommandType() == CT_ConditionType)
		{
			if (PlayerCommand* newConditionCommand = creator->Create(conditionToken->GetText(), Controller))
			{
				if (ConditionCommand* condCommand = dynamic_cast<ConditionCommand*>(newConditionCommand))
				{
					instanceCommand = dynamic_cast<CommandT*>(creator->Create(Command, Controller, condCommand));
					if (instanceCommand)
					{
						commandList->PushCommand(instanceCommand);
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
			Log->PushMessageLog("Keyword \"NotEnd\" doesn't expect negating...", WarningMes);
		}
		else
		{
			const std::string What = Command;
			const std::string Exactly = " expects ConditionCommand...";
			const std::string WhatExactly = What + Exactly;
			
			Log->PushMessageLog(WhatExactly, ErrorMes);
		}
		return instanceCommand;
	}

	template<typename CommandType>
	bool Parser::FillScope(CommandType* Command, void(CommandType::* PushCommand)(PlayerCommand*), const bool HasCondition)
	{
		Token* beginToken = Tokens.front().Get();
		MacroCommand* macroElseCommandList = new MacroCommand();
		if (beginToken->GetCommandType() == CT_BeginScope && HasCondition)
		{
			if (!FillCommandListScope(macroElseCommandList))
			{
				return false;
			}
			for (PlayerCommand* commandToAdd : macroElseCommandList->GetList())
			{
				(Command->*PushCommand)(commandToAdd);
			}
		}
		else
		{
			Log->PushMessageLog("While/IfCommand hasn't Scope...", ErrorMes);
			return false;
		}
		return true;
	}
}

#endif