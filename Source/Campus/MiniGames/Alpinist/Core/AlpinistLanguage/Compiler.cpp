#ifdef ALPINIST_GAME

#include "Compiler.h"

#include "../GameController.h"
#include "Lexer.h"
#include "Parser.h"

void AlpinistGame::Compiler::SetCode(const std::string& NewCode)
{
	Code = NewCode;
}

bool AlpinistGame::Compiler::Compile(AlpinistLog& AlpLog)
{
	AlpLog.ClearLog();
	if (Controller)
	{
		Controller->ClearHistory();
	}
	
	Lexer lexer = Lexer(Code);
	std::vector<TSharedPtr<Token>> Tokens = *lexer.LexAnalysis(AlpLog);
	if (AlpLog.bHasErrors)
	{
		return false;
	}

	Parser parser(Tokens, Controller);
	Commands = parser.SynAnalysis(AlpLog);
	if (AlpLog.bHasErrors || AlpLog.bHasWarnings || !Commands)
	{
		return false;
	}

	return true;
}

bool AlpinistGame::Compiler::Run(AlpinistLog& AlpLog)
{
    if (!Compile(AlpLog))
    {
	    return false;
    }

	const bool result = Commands->Execute(&AlpLog);
	if (result)
	{
		Controller->SaveCopyOfWorld(nullptr);
	}
	return result;
}
#endif