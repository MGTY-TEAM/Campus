#pragma once

#include <map>
#include <regex>
#include <string>
#include "../Commands.h"

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
		TokenType(const std::string name, ECommandType commandType, std::regex* regular) : Name(name), CommandType(commandType), Regular(regular) {}
		~TokenType()
		{
			// delete Regular;
		}

		std::string GetName() const { return Name; };
		std::regex* GetRegular() const { return Regular; };
		ECommandType GetCommandType() const { return CommandType; }
	};
}



