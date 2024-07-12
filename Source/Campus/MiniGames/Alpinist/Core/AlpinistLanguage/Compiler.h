#pragma once

// #include "../GameController.h"
#include "Lexer.h"
#include "Parser.h"

#ifdef ALPINIST_GAME
namespace AlpinistGame
{
	class Compiler
	{
		GameController* Controller;
		std::string Code;

		MacroCommand* Commands = nullptr;
	public:
		Compiler(GameController* controller, const std::string& code) : Controller(controller), Code(code) {}

		bool Compile(AlpinistLog& AlpLog);
		bool Run(AlpinistLog& AlpLog);

		MacroCommand* GetListOfCommands() { return Commands; };
	};
}

#endif