#pragma once

#ifdef ALPINIST_GAME

namespace AlpinistGame
{
	class GameController;
	class MacroCommand;
	class AlpinistLog;
	
	class Compiler
	{
		TWeakPtr<GameController> Controller;
		std::string Code;

		TSharedPtr<MacroCommand> Commands = nullptr;
	public:
		Compiler(const TWeakPtr<GameController>& controller, const std::string& code) : Controller(controller), Code(code) {}

		void SetCode(const std::string& NewCode);
		bool Compile(TWeakPtr<AlpinistLog>& AlpLog);
		bool Run(TWeakPtr<AlpinistLog>& AlpLog);

		TSharedPtr<MacroCommand> GetListOfCommands() { return Commands; };

		int32 CountTokens();
		FString GetCode() const;
	};
}

#endif