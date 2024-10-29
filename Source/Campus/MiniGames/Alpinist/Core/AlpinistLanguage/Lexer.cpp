#include "Lexer.h"
// #include "../GameController.h"
#ifdef ALPINIST_GAME
std::vector<TSharedPtr<AlpinistGame::Token>>* AlpinistGame::Lexer::LexAnalysis(AlpinistLog& AlpLog)
{
	Log = &AlpLog;
	while (ContinueLexAnal())
	{

	}
	return &Tokens;
}

bool AlpinistGame::Lexer::ContinueLexAnal()
{
	if (arr.size() == 0)
	{
		return false;
	}
	std::cmatch result;

	const char* ch = &arr.front()[0];
	for (TSharedPtr<TokenType> TokenTypeValue : TokenList)
	{
		if (std::regex_match(ch, result, TokenTypeValue->GetRegular()))
		{
			TSharedPtr<Token> token = MakeShared<Token>(TokenTypeValue, TokenTypeValue->GetName(), currentPos++);
			Tokens.push_back(token);
			arr.erase(arr.begin());
			return true;
		}
	}

	const std::string What = "Undefined Command: ";
	const std::string Exactly = arr.front();
	const std::string WhatExactly = What + Exactly;
	const std::string InPos = std::to_string(currentPos);
	
	Log->PushMessageLog(InPos + ": " + WhatExactly, AlpinistGame::ErrorMes);
	
	Log->PushMessageLog(InPos + ": " + "Incorrect Command", AlpinistGame::ErrorMes);
	return false;
}

void AlpinistGame::Lexer::GetNamesOfTokens() const
{
	for (auto Token : Tokens)
	{
		// std::cout << Token->GetText() << std::endl;
	}
}

bool AlpinistGame::Lexer::DivideStr(std::string str, std::vector<std::string>& arrToFill)
{
	if (str.empty())
		return false;

	size_t pos;
	while ((pos = str.find("\r")) != std::string::npos)
	{
		str.erase(pos, 1);
		str.insert(pos, " ");
	}
	while ((pos = str.find("\n")) != std::string::npos)
	{
		str.erase(pos, 1);
		str.insert(pos, " ");
	}
	while ((pos = str.find('\t')) != std::string::npos)
	{
		str.erase(pos, 1);
		str.insert(pos, " ");
	}

	std::string delim(" ");
	size_t delta = delim.length();
	size_t prev = 0;
	size_t next;
	while ((next = str.find(delim, prev)) != std::string::npos)
	{
		std::string tmp = str.substr(prev, next - prev);
		PushAndAdjustment(tmp, arrToFill);
		prev = next + delta;
	}
	std::string tmp = str.substr(prev);
	PushAndAdjustment(tmp, arrToFill);

	return true;
}

void AlpinistGame::Lexer::PushAndAdjustment(std::string str, std::vector<std::string>& arrToFill)
{
	if (str.size() != 0)
	{
		arrToFill.push_back(str);
	}
}
#endif