#pragma once

#include "World.h"
// #include "Commands.h"
#include "AlpinistMemento.h"

#ifdef ALPINIST_GAME

class PlayerCommand;
class AlpinistMemento;
class AlpinistCaretaker;

namespace AlpinistGame
{
	enum TypeOfLog
	{
		DisplayMes = 0,
		WarningMes = 1,
		ErrorMes = 2,
		SuccessMes = 3
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

		void ClearLog()
		{
			ListOfLog.clear();
			ListOfLog.shrink_to_fit();

			bHasErrors = false;
			bHasWarnings = false;
			CountOfLog = 0;
		}

		std::vector<MessageLog>* GetListOfLog() { return &ListOfLog; }
		
		bool bHasWarnings = false;
		bool bHasErrors = false;
	};
	
	class GameController
	{
		TSharedPtr<World> m_world;
		std::vector<std::string> m_initialWorld;

		TSharedPtr<AlpinistGame::AlpinistCaretaker> m_alpinistCaretaker;
	public:
		GameController();
		GameController(const std::vector<std::string>& map);

		bool MoveForward();
		bool RotateRight();
		bool RotateLeft();

		bool WallInDirection(const Condition& condition);
		bool PlayerNotOnFinish();

		void SetNewMap(const std::vector<std::string>& map);
		TSharedPtr<World> GetWorld() { return m_world; }

		void ToStartPositions();
		bool SaveCopyOfWorld(PlayerCommand* Command);
		bool RestoreOfWorld(PlayerCommand* Command);
		TWeakPtr<AlpinistGame::AlpinistCaretaker> GetAlpinistCaretaker() const { return m_alpinistCaretaker.ToWeakPtr(); }
		// bool ExecuteMacroCommand(MacroCommand* macroCommand);
	};
}
#endif