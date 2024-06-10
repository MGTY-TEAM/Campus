#include "Lexer.h"
#include "../GameController.h"
#ifdef ALPINIST_GAME
std::vector<AlpinistGame::Token*>* AlpinistGame::Lexer::LexAnalysis(AlpinistLog& AlpLog)
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
	for (TokenType* TokenTypeValue : TokenList)
	{
		if (std::regex_match(ch, result, *TokenTypeValue->GetRegular()))
		{

			// std::cout << result[0].str() << std::endl;
			Token* token = new Token(TokenTypeValue, TokenTypeValue->GetName(), currentPos++);
			Tokens.push_back(token);
			arr.erase(arr.begin());
			return true;
		}
	}

	Log->PushMessageLog("Incorrect Command", ErrorMes);
	// std::cout << "Incorrect Command" << std::endl;
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
	while ((pos = str.find("\r\n")) != std::string::npos)
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
		// std::cout << tmp << std::endl;
	}
	std::string tmp = str.substr(prev);
	PushAndAdjustment(tmp, arrToFill);

	// std::cout << tmp << std::endl;

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