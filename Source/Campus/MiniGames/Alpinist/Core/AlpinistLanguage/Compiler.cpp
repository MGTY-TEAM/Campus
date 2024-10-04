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
	// AlpLog.ClearLog();
	
	Lexer lexer = Lexer(Code);
	std::vector<Token*> Tokens = *lexer.LexAnalysis(AlpLog);
	if (AlpLog.bHasErrors)
	{
		return false;
	}

	Parser parser(Tokens, Controller);
	Commands = parser.SynAnalysis(AlpLog);
	if (AlpLog.bHasErrors || !Commands)
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
	
	return Commands->Execute();
}
#endif