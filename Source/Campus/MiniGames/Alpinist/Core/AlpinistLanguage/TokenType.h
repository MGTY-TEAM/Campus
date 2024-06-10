#pragma once

#include <map>
#include <regex>
#include <string>
#include "../Commands.h"
#include "../GameController.h"
#ifdef ALPINIST_GAME
namespace AlpinistGame
{
	enum ECommandType
	{
		SimpleCommand = 0,
		WhileLoop = 1,
		IfElseConditional = 2,
		ConditionType = 3,
		BeginScope = 4,
		EndScope = 5,
		Negate = 6,
		Space = 7
	};

	class TokenType
	{
	protected:
		std::string Name;
		ECommandType CommandType;
		std::regex* Regular;

	public:
		TokenType(const std::string name, ECommandType commandType, std::regex* regularexpr) : Name(name), CommandType(commandType), Regular(regularexpr) {}
		~TokenType()
		{
			// delete Regular;
		}

		std::string GetName() const { return Name; };
		std::regex* GetRegular() const { return Regular; };
		ECommandType GetCommandType() const { return CommandType; }
	};
}
#endif