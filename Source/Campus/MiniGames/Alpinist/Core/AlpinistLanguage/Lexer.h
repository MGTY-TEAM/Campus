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
			new TokenType("move", CT_SimpleCommand, new std::regex("(-\\.-)")),
			new TokenType("right", CT_SimpleCommand, new std::regex("(\\.-)")),
			new TokenType("left", CT_SimpleCommand, new std::regex("(-\\.)")),
			new TokenType("wallAhead", CT_ConditionType, new std::regex("(---)")),
			new TokenType("wallRight", CT_ConditionType, new std::regex("(\\.--)")),
			new TokenType("wallLeft", CT_ConditionType, new std::regex("(--\\.)")),
			new TokenType("while", CT_WhileLoop, new std::regex("(\\.-\\.)")),
			new TokenType("if", CT_IfElseConditional, new std::regex("(\\.\\.)")),
			new TokenType("else", CT_IfElseConditional, new std::regex("(--)")),
			new TokenType("begin", CT_BeginScope, new std::regex("(\\.)")),
			new TokenType("end", CT_EndScope, new std::regex("(-)")),
			new TokenType("Space", CT_Space, new std::regex("(\\s)")),
			new TokenType("Negate", CT_Negate, new std::regex("(\\.\\.\\.)")),
			new TokenType("NotEnd", CT_NotEnd, new std::regex("(-\\.\\.-)"))
		};
	};
}

#endif