#pragma once

#ifdef ALPINIST_GAME

namespace AlpinistGame
{
	class GameController;
	class MacroCommand;
	class AlpinistLog;
	
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