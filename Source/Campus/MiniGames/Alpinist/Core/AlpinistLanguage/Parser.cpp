#include "Parser.h"
// #include "../GameController.h"
#ifdef ALPINIST_GAME
AlpinistGame::Parser::~Parser()
{
	/* for (auto token : Tokens)
	{
		delete token;
	}
	delete Controller;
	delete CommandList;
	delete creator; */
}

AlpinistGame::MacroCommand* AlpinistGame::Parser::SynAnalysis(AlpinistLog& AlpLog)
{
	Log = &AlpLog;
	while (ContinueSynAnal(CommandList))
	{

	}

	if (Tokens.size() == 0 && CheckStackScope())
	{
		return CommandList;
	}
	return nullptr;
}

bool AlpinistGame::Parser::ContinueSynAnal(MacroCommand* commandList)
{
	if (Tokens.size() == 0)
	{
		return false;
	}

	Token* token = Tokens.front();
	switch (token->GetCommandType())
	{
	case SimpleCommand:
		if (AddSimpleCommand(token->GetText(), commandList))
		{
			return true;
		}
		Log->PushMessageLog("Undefined Command: Can't create command", ErrorMes);
		// std::cout << "Undefined Command: Can't create command" << std::endl;
		break;
	case WhileLoop:
		if (AddWhileLoop(token->GetText(), commandList))
		{
			return true;
		}
		Log->PushMessageLog("Incorrect WhileLoop", ErrorMes);
		// std::cout << "Incorrect WhileLoop" << std::endl;
		break;
	case IfElseConditional:
		if (AddIfElseConditional(token->GetText(), commandList))
		{
			return true;
		}
		Log->PushMessageLog("Incorrect IfElseConditional", ErrorMes);
		// std::cout << "Incorrect IfElseConditional" << std::endl;
		break;
	case ConditionType:
		Log->PushMessageLog("Expected while Or if Command", ErrorMes);
		// std::cout << "Expected while Or if Command" << std::endl;
		break;
	case BeginScope:
		Log->PushMessageLog("Expected while Or if Command", ErrorMes);
		// std::cout << "Expected while Or if Command" << std::endl;
		break;
	case EndScope:
		Log->PushMessageLog("Expected while Or if Command", ErrorMes);
		// std::cout << "Expected while Or if Command" << std::endl;
		break;
	case Space:
		Tokens.erase(Tokens.begin());
		return true;
	default:
		Log->PushMessageLog("Undefined Type: Can't create command", ErrorMes);
		break;
		// std::cout << "Undefined Type: Can't create command" << std::endl;
	}
	return false;
}

bool AlpinistGame::Parser::AddSimpleCommand(const std::string& Command, MacroCommand* commandList)
{
	if (PlayerCommand* newCommand = creator->Create(Command, Controller))
	{
		commandList->PushCommand(newCommand);
		Tokens.erase(Tokens.begin());
		return true;
	}
	return false;
}

bool AlpinistGame::Parser::AddWhileLoop(const std::string& Command, MacroCommand* commandList)
{
	if (!DeleteTokenFront())
	{
		return false;
	}

	// Check that next token is condition
	bool whileHasCondition = false;
	WhileCommand* whileCommand = CreateCommandWithCondtion<WhileCommand>(Command, commandList, whileHasCondition);
	if (!whileCommand)
	{
		return false;
	}

	// Check that next token is begin for
	if (FillScope<WhileCommand>(whileCommand, &WhileCommand::PushCommand, whileHasCondition))
	{
		return true;
	}

	return false;
}

bool AlpinistGame::Parser::AddIfElseConditional(const std::string& Command, MacroCommand* commandList)
{
	if (!DeleteTokenFront())
	{
		return false;
	}

	bool ifHasCondition = false;
	IfCommand* ifCommand = CreateCommandWithCondtion<IfCommand>(Command, commandList, ifHasCondition);
	if (!ifCommand)
	{
		return false;
	}

	// Check that next token is begin for if
	if (!FillScope<IfCommand>(ifCommand, &IfCommand::PushCommandInTrueIf, ifHasCondition))
	{
		return false;
	}

	if (Tokens.size() != 0)
	{
		if (Token* elseToken = Tokens.front())
		{
			if (elseToken->GetText() == "else")
			{
				if (!DeleteTokenFront())
				{
					return false;
				}

				// Check that next token is begin for else
				if (FillScope<IfCommand>(ifCommand, &IfCommand::PushCommandInFalseIf))
				{
					return true;
				}
			}
			else
			{
				return true;
			}
		}
	}
	else
	{
		return true;
	}

	return false;
}

bool AlpinistGame::Parser::DeleteTokenFront()
{
	if (Tokens.size() != 0)
	{
		Tokens.erase(Tokens.begin());
	}
	else if (Tokens.size() == 0)
	{
		return false;
	}
	SkipSpaceTokenIfThereItIs(Tokens.front());
	return true;
}

bool AlpinistGame::Parser::FillCommandListScope(MacroCommand* macroCommandList)
{
	if (!DeleteTokenFront())
	{
		return false;
	}
	StackScope.push(0);

	Token* endToken = Tokens.front();
	while (endToken->GetCommandType() != EndScope)
	{
		if (!ContinueSynAnal(macroCommandList))
		{
			return false;
		}
		endToken = Tokens.front();
	}
	if (!DeleteTokenFront())
	{
		return false;
	}
	StackScope.push(1);
	return true;
}

bool AlpinistGame::Parser::CheckStackScope()
{
	int count = 0;
	while (StackScope.size() != 0)
	{
		if (StackScope.top() == 1)
		{
			++count;
		}
		else
		{
			--count;
		}
		StackScope.pop();
	}

	if (StackScope.size() == 0)
	{
		return true;
	}
	return false;
}

void AlpinistGame::Parser::SkipSpaceTokenIfThereItIs(Token* token)
{
	if (token->GetCommandType() == Space)
	{
		Tokens.erase(Tokens.begin());
	}
}

void AlpinistGame::Parser::GetNamesOfTokens() const
{
	for (auto Token : Tokens)
	{
		// std::cout << Token->GetText() << std::endl;
	}
}
#endif