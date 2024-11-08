#ifdef ALPINIST_GAME

#include "Compiler.h"

#include "../GameController.h"
#include "Lexer.h"
#include "Parser.h"

void AlpinistGame::Compiler::SetCode(const std::string& NewCode)
{
	Code = NewCode;
}

bool AlpinistGame::Compiler::Compile(TWeakPtr<AlpinistLog>& AlpLog)
{
	AlpLog.Pin()->ClearLog();
	if (Controller.IsValid())
	{
		Controller.Pin()->ClearHistory();
	}
	
	Lexer lexer = Lexer(Code);
	std::vector<TSharedPtr<Token>> Tokens = *lexer.LexAnalysis(AlpLog);
	if (AlpLog.Pin()->bHasErrors)
	{
		return false;
	}

	Parser parser(Tokens, Controller);
	Commands = parser.SynAnalysis(AlpLog);
	if (AlpLog.Pin()->bHasErrors || AlpLog.Pin()->bHasWarnings || !Commands)
	{
		return false;
	}

	return true;
}

bool AlpinistGame::Compiler::Run(TWeakPtr<AlpinistLog>& AlpLog)
{
    if (!Compile(AlpLog))
    {
	    return false;
    }

	const bool result = Commands->Execute(AlpLog);
	if (result)
	{
		Controller.Pin()->SaveCopyOfWorld(nullptr);
	}
	return result;
}
#endif