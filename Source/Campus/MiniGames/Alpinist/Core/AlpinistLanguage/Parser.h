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
		std::vector<Token*> Tokens;
		size_t Pos = 0;
		GameController* Controller;
		MacroCommand* CommandList;
		Creator* creator;

		AlpinistLog* Log = nullptr;
	public:
		Parser(const std::vector<Token*>& ListOfTokens, GameController* controller) : Tokens(ListOfTokens), Controller(controller)
		{
			CommandList = new MacroCommand();
			creator = new Creator();
		}
		~Parser();

		MacroCommand* SynAnalysis(AlpinistLog& AlpLog);
	private:
		bool ContinueSynAnal(MacroCommand* commandList);

		bool AddSimpleCommand(const std::string& Command, MacroCommand* commandList);
		bool AddWhileLoop(const std::string& Command, MacroCommand* commandList);
		bool AddIfElseConditional(const std::string& Command, MacroCommand* commandList);

		template<typename CommandType>
		CommandType* CreateCommandWithCondtion(const std::string& Command, MacroCommand* commandList, bool& CommandHasCondition);

		template<typename CommandType>
		bool FillScope(CommandType* Command, void(CommandType::* PushCommand)(PlayerCommand*), const bool HasCondition = true);
		bool FillCommandListScope(MacroCommand* macroCommandList);

		bool DeleteTokenFront();
		bool CheckStackScope();
		void SkipSpaceTokenIfThereItIs(Token* token);
	public:
		void GetNamesOfTokens() const;
	};

	template<typename CommandT>
	CommandT* Parser::CreateCommandWithCondtion(const std::string& Command, MacroCommand* commandList, bool& CommandHasCondition)
	{
		bool NeedToBeNegate = false;
		Token* NegateToken = Tokens.front();
		if (NegateToken->GetCommandType() == Negate)
		{
			NeedToBeNegate = true;
			DeleteTokenFront();
		}

		Token* conditionToken = Tokens.front();
		CommandT* instanceCommand = nullptr;
		if (conditionToken->GetCommandType() == ConditionType)
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
		return instanceCommand;
	}

	template<typename CommandType>
	bool Parser::FillScope(CommandType* Command, void(CommandType::* PushCommand)(PlayerCommand*), const bool HasCondition)
	{
		Token* beginToken = Tokens.front();
		MacroCommand* macroElseCommandList = new MacroCommand();
		if (beginToken->GetCommandType() == BeginScope && HasCondition)
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
			return false;
		}
		return true;
	}
}

#endif