#include "Compiler.h"
// #include "../GameController.h"
#ifdef ALPINIST_GAME
bool AlpinistGame::Compiler::Compile(AlpinistLog& AlpLog)
{
	Lexer lexer = Lexer(Code);
	std::vector<Token*> Tokens = *lexer.LexAnalysis(AlpLog);
	// std::vector<Token*> Tokens(std::move(*lexer.LexAnalysis(AlpLog)));
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