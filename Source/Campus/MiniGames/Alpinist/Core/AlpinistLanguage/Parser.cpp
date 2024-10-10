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

TSharedPtr<AlpinistGame::MacroCommand> AlpinistGame::Parser::SynAnalysis(AlpinistLog& AlpLog)
{
	Log = &AlpLog;
	while (ContinueSynAnal(CommandList.Get()))
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

	Token* token = Tokens.front().Get();
	switch (token->GetCommandType())
	{
	case CT_SimpleCommand:
		if (AddSimpleCommand(token->GetText(), commandList))
		{
			return true;
		}
		Log->PushMessageLog("Undefined Command: Can't create command...", ErrorMes);
		break;
	case CT_WhileLoop:
		if (AddWhileLoop(token->GetText(), commandList))
		{
			return true;
		}
		Log->PushMessageLog("Incorrect WhileLoop...", ErrorMes);
		break;
	case CT_IfElseConditional:
		if (AddIfElseConditional(token->GetText(), commandList))
		{
			return true;
		}
		Log->PushMessageLog("Incorrect IfElseConditional...", ErrorMes);
		break;
	case CT_ConditionType:
		Log->PushMessageLog("Expected while Or if Command...", ErrorMes);
		break;
	case CT_BeginScope:
		Log->PushMessageLog("Expected while Or if Command...", ErrorMes);
		break;
	case CT_EndScope:
		Log->PushMessageLog("Expected while Or if Command...", ErrorMes);
		break;
	case CT_Space:
		Tokens.erase(Tokens.begin());
		return true;
	case CT_NotEnd:
		Log->PushMessageLog("Expected while Command...", ErrorMes);
		break;
	default:
		Log->PushMessageLog("Undefined Type: Can't create command...", ErrorMes);
		break;
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
	
	Log->PushMessageLog(std::string("Creator can't create Command: ") + Command ,ErrorMes);
	return false;
}

bool AlpinistGame::Parser::AddWhileLoop(const std::string& Command, MacroCommand* commandList)
{
	if (!DeleteTokenFront())
	{
		return false;
	}

	bool whileShouldBeFill = false;
	WhileCommand* whileCommand = nullptr;
	
	// Check keywords
	if (CheckKeywords())
	{
		whileCommand = CreateWhileCommandWithKeyword(Command, commandList, whileShouldBeFill);
	}
	else
	{
		// Check that next token is condition
		whileCommand = CreateCommandWithCondition<WhileCommand>(Command, commandList, whileShouldBeFill);
	}
	
	if (!whileCommand)
	{
		Log->PushMessageLog("Can't create WhileCommand...", ErrorMes);
		return false;
	}

	// Check that next token is begin for
	if (FillScope<WhileCommand>(whileCommand, &WhileCommand::PushCommand, whileShouldBeFill))
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
	IfCommand* ifCommand = CreateCommandWithCondition<IfCommand>(Command, commandList, ifHasCondition);
	if (!ifCommand)
	{
		Log->PushMessageLog("Can't create IfCommand...", ErrorMes);
		return false;
	}

	// Check that next token is begin for if
	if (!FillScope<IfCommand>(ifCommand, &IfCommand::PushCommandInTrueIf, ifHasCondition))
	{
		return false;
	}

	if (Tokens.size() != 0)
	{
		if (Token* elseToken = Tokens.front().Get())
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

AlpinistGame::WhileCommand* AlpinistGame::Parser::CreateWhileCommandWithKeyword(const std::string& Command, MacroCommand* commandList, bool& CommandHasCondition)
{
	WhileCommand* whileCommand = nullptr;
	
	Token* nextToken = Tokens.front().Get();
	if (nextToken->GetCommandType() == CT_NotEnd)
	{
		if (PlayerCommand* newNotEndCommand = creator->Create(nextToken->GetText(), Controller))
		{
			if (NotEndCommand* notEndCommand = dynamic_cast<NotEndCommand*>(newNotEndCommand))
			{
				whileCommand = dynamic_cast<WhileCommand*>(creator->CreateWhileNotEnd(Command, Controller, notEndCommand));
				if (whileCommand)
				{
					commandList->PushCommand(whileCommand);
					DeleteTokenFront();

					CommandHasCondition = true;
				}
			}
		}
	}

	if (!whileCommand)
	{
		Log->PushMessageLog("Can't create NotEndCommand...", ErrorMes);
	}

	return whileCommand;
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
	SkipSpaceTokenIfThereItIs(Tokens.front().Get());
	return true;
}

bool AlpinistGame::Parser::FillCommandListScope(MacroCommand* macroCommandList)
{
	if (!DeleteTokenFront())
	{
		return false;
	}
	StackScope.push(0);

	Token* endToken = Tokens.front().Get();
	while (endToken->GetCommandType() != CT_EndScope)
	{
		if (!ContinueSynAnal(macroCommandList))
		{
			return false;
		}
		endToken = Tokens.front().Get();
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
	if (token->GetCommandType() == CT_Space)
	{
		Tokens.erase(Tokens.begin());
	}
}

bool AlpinistGame::Parser::CheckKeywords()
{
	Token* token = Tokens.front().Get();
	if (token && token->GetCommandType() == CT_NotEnd)
	{
		return true;
	}
	
	return false;
}

void AlpinistGame::Parser::GetNamesOfTokens() const
{
	for (auto Token : Tokens)
	{
		// std::cout << Token->GetText() << std::endl;
	}
}
#endif