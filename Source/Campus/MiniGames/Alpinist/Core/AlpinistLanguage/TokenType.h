#pragma once

// #include <map>
#include <regex>
#include <string>
#include "../Commands.h"
#include "../GameController.h"
#ifdef ALPINIST_GAME
namespace AlpinistGame
{
	enum ECommandType
	{
		CT_SimpleCommand = 0,
		CT_WhileLoop = 1,
		CT_IfElseConditional = 2,
		CT_ConditionType = 3,
		CT_BeginScope = 4,
		CT_EndScope = 5,
		CT_Negate = 6,
		CT_Space = 7,
		CT_NotEnd = 8
	};

	class TokenType
	{
	protected:
		std::string Name;
		ECommandType CommandType;
		std::regex Regular;

	public:
		TokenType(const std::string& name, ECommandType commandType, const std::regex& regularexpr) : Name(name), CommandType(commandType), Regular(regularexpr) {}
		~TokenType()
		{
			// Regular.reset();
		}

		std::string GetName() const { return Name; };
		std::regex GetRegular() const { return Regular; };
		ECommandType GetCommandType() const { return CommandType; }
	};
}
#endif