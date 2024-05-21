#include "Compiler.h"

bool AlpinistGame::Compiler::Run()
{
    Lexer lexer = Lexer(Code);
    const std::vector<Token*> Tokens = lexer.LexAnalysis();

    Parser parser(Tokens, Controller);
    parser.GetNamesOfTokens();
    MacroCommand* Commands = parser.SynAnalysis();
	
	return Commands->Execute();
}
