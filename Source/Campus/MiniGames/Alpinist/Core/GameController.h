#pragma once
// #define ALPINIST_GAME

// #include "Commands.h"
#include "World.h"
#ifdef ALPINIST_GAME
namespace AlpinistGame
{
	enum TypeOfLog
	{
		DisplayMes = 0,
		WarningMes = 1,
		ErrorMes = 2
	};

	struct MessageLog
	{
		std::string Message;
		TypeOfLog Type;
	};
	
	class AlpinistLog
	{
		uint8_t CountOfLog;
		std::vector<MessageLog> ListOfLog{};
	
	public:
		AlpinistLog() : CountOfLog(0) {}

		void PushMessageLog(const std::string& Message, const TypeOfLog Type)
		{
			if (Type == WarningMes) bHasWarnings = true;
			if (Type == ErrorMes) bHasErrors = true;
			
			const MessageLog Log(Message, Type);
			ListOfLog.push_back(Log);
		}

		std::vector<MessageLog>* GetListOfLog() { return &ListOfLog; }
		
		bool bHasWarnings = false;
		bool bHasErrors = false;
	};
	
	class GameController
	{
		World* m_world;

	public:
		GameController();
		GameController(const std::vector<std::string>& map);

		bool MoveForward();
		bool RotateRight();
		bool RotateLeft();

		bool WallInDirection(const Condition& condition);
		bool PlayerNotOnFinish();

		World* GetWorld() { return m_world; }

		// bool ExecuteMacroCommand(MacroCommand* macroCommand);
	};
}
#endif