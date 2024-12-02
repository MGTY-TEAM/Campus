#pragma once

#include <string>
#include "Token.h"

#ifdef ALPINIST_GAME

namespace AlpinistGame
{
	class Lexer
	{
		std::string Code;
		size_t currentPos = 0;
		std::vector<TSharedPtr<Token>> Tokens = {};
		std::vector<std::string> arr;

		TWeakPtr<AlpinistLog> Log = nullptr;
	public:
		Lexer(const std::string& code) : Code(code)
		{
			DivideStr(code, arr);
		}
		~Lexer()
		{
			for (auto token : Tokens)
			{
				// token.reset();
			} 
		}

		std::vector<TSharedPtr<Token>>* LexAnalysis(TWeakPtr<AlpinistLog>& AlpLog);

		void GetNamesOfTokens() const;
	private:
		bool ContinueLexAnal();

		bool DivideStr(std::string str, std::vector<std::string>& arr);
		void PushAndAdjustment(std::string str, std::vector<std::string>& arr);

		std::list<TSharedPtr<TokenType>> TokenList = {
			MakeShared<TokenType>("move", CT_SimpleCommand, std::regex("(-\\.-)")),
			MakeShared<TokenType>("right", CT_SimpleCommand, std::regex("(\\.-)")),
			MakeShared<TokenType>("left", CT_SimpleCommand, std::regex("(-\\.)")),
			MakeShared<TokenType>("wallAhead", CT_ConditionType, std::regex("(---)")),
			MakeShared<TokenType>("wallRight", CT_ConditionType, std::regex("(\\.--)")),
			MakeShared<TokenType>("wallLeft", CT_ConditionType, std::regex("(--\\.)")),
			MakeShared<TokenType>("while", CT_WhileLoop, std::regex("(\\.-\\.)")),
			MakeShared<TokenType>("if", CT_IfElseConditional, std::regex("(\\.\\.)")),
			MakeShared<TokenType>("else", CT_IfElseConditional, std::regex("(--)")),
			MakeShared<TokenType>("begin", CT_BeginScope, std::regex("(\\.)")),
			MakeShared<TokenType>("end", CT_EndScope, std::regex("(-)")),
			MakeShared<TokenType>("Space", CT_Space, std::regex("(\\s)")),
			MakeShared<TokenType>("Negate", CT_Negate, std::regex("(\\.\\.\\.)")),
			MakeShared<TokenType>("NotEnd", CT_NotEnd, std::regex("(-\\.\\.-)"))
		};
	};
}

#endif