#pragma once

#include <string>
#include "TokenType.h"
// #include "../GameController.h"
#ifdef ALPINIST_GAME
namespace AlpinistGame
{
	class Token
	{
		TSharedPtr<TokenType> Type;
		std::string Text;
		size_t Pos;

	public:
		Token(TSharedPtr<TokenType> type, std::string text, size_t pos) : Type(type), Text(text), Pos(pos) {}
		~Token()
		{
			// Type.reset();
		}

		std::string GetText() const { return Text; }
		ECommandType GetCommandType() const { return Type->GetCommandType(); }
	};
}

#endif