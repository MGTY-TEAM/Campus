#pragma once

#include <string>
#include "Token.h"
// #include "../GameController.h"
#ifdef ALPINIST_GAME
namespace AlpinistGame
{
	class Lexer
	{
		std::string Code;
		size_t currentPos = 0;
		std::vector<Token*> Tokens = {};
		std::vector<std::string> arr;

		AlpinistLog* Log = nullptr;
	public:
		Lexer(const std::string& code) : Code(code)
		{
			DivideStr(code, arr);
		}
		~Lexer()
		{
			/* for (auto token : Tokens)
			{
				delete token;
			} */
		}

		std::vector<Token*>* LexAnalysis(AlpinistLog& AlpLog);

		void GetNamesOfTokens() const;
	private:
		bool ContinueLexAnal();

		bool DivideStr(std::string str, std::vector<std::string>& arr);
		void PushAndAdjustment(std::string str, std::vector<std::string>& arr);

		std::list<TokenType*> TokenList = {
			new TokenType("move", SimpleCommand, new std::regex("(-\\.-)")),
			new TokenType("right", SimpleCommand, new std::regex("(\\.-)")),
			new TokenType("left", SimpleCommand, new std::regex("(-\\.)")),
			new TokenType("wallAhead", ConditionType, new std::regex("(---)")),
			new TokenType("wallRight", ConditionType, new std::regex("(\\.--)")),
			new TokenType("wallLeft", ConditionType, new std::regex("(--\\.)")),
			new TokenType("while", WhileLoop, new std::regex("(\\.-\\.)")),
			new TokenType("if", IfElseConditional, new std::regex("(\\.\\.)")),
			new TokenType("else", IfElseConditional, new std::regex("(--)")),
			new TokenType("begin", BeginScope, new std::regex("(\\.)")),
			new TokenType("end", EndScope, new std::regex("(-)")),
			new TokenType("Space", Space, new std::regex("(\\s)")),
			new TokenType("Negate", Negate, new std::regex("(\\.\\.\\.)")),
		};
	};
}

#endif