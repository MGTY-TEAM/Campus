#pragma once

#include <string>
#include "TokenType.h"
#include "../GameController.h"
#ifdef ALPINIST_GAME
namespace AlpinistGame
{
	class Token
	{
		TokenType* Type;
		std::string Text;
		size_t Pos;

	public:
		Token(TokenType* type, std::string text, size_t pos) : Type(type), Text(text), Pos(pos) {}
		~Token()
		{
			// delete Type;
		}

		std::string GetText() const { return Text; }
		ECommandType GetCommandType() const { return Type->GetCommandType(); }
	};
}

#endif