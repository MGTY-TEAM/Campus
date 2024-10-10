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

		TSharedPtr<MacroCommand> Commands = nullptr;
	public:
		Compiler(GameController* controller, const std::string& code) : Controller(controller), Code(code) {}

		void SetCode(const std::string& NewCode);
		bool Compile(AlpinistLog& AlpLog);
		bool Run(AlpinistLog& AlpLog);

		TSharedPtr<MacroCommand> GetListOfCommands() { return Commands; };
	};
}

#endif