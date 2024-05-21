#pragma once

#include "../GameController.h"
#include "Lexer.h"
#include "Parser.h"

namespace AlpinistGame
{
	class Compiler
	{
		GameController* Controller;
		std::string Code;

	public:
		Compiler(GameController* controller, const std::string& code) : Controller(controller), Code(code) {}

		bool Run();
	};
}