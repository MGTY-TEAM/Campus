#ifdef ALPINIST_GAME
#if WITH_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UHelperReaderJsonForAlpinist.h"
#include "Campus/Libraries/CampusUtils.h"
#include "Campus/MiniGames/Alpinist/Core/GameController.h"
#include "Campus/MiniGames/Alpinist/Core/AlpinistLanguage/Compiler.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FExpectLexerErrors, "Campus.Alpinist.ExpectLexerErrors",
                                 EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FExpectWhileErrors, "Campus.Alpinist.EcpectWhileErrors",
								 EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FExpectIfElseErrors, "Campus.Alpinist.EcpectIfElseErrors",
								 EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FExpectInfiniteCycleError, "Campus.Alpinist.EcpectInfiniteCycleError",
								 EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)

bool FExpectLexerErrors::RunTest(const FString& Parameters)
{
	const FString PathToJson = UKismetSystemLibrary::GetProjectDirectory() + "Alpinist/Levels/Tests/ToBeFailedTestsMap.json";
	bool SucceededDeserialize = false;
	
	FString OutInfoMessage;

	const TSharedPtr<FJsonObject> JsonObject = UHelperReaderJsonForAlpinist::ReadJson(PathToJson, SucceededDeserialize, OutInfoMessage);
	TestTrue(OutInfoMessage, SucceededDeserialize);
	
	TArray<FString> Map;
	TestTrue("Not Array", JsonObject->TryGetStringArrayField("game_map", Map));

	const std::vector<std::string> TestMap = CampusUtils::TArrayOfStringToVectorOfString(Map);

	TSharedPtr<AlpinistGame::GameController> controller = MakeShared<AlpinistGame::GameController>(TestMap);
	
	TSharedPtr<AlpinistGame::Compiler> compiler = MakeShared<AlpinistGame::Compiler>(controller, "--.-.-");

	TSharedPtr<AlpinistGame::AlpinistLog> Log = MakeShared<AlpinistGame::AlpinistLog>();
	TWeakPtr<AlpinistGame::AlpinistLog> WeakLog = Log.ToWeakPtr();
	const bool CompileSuccess = compiler->Compile(WeakLog);
	if (!CompileSuccess)
	{
		for (const AlpinistGame::MessageLog ErrorMessage : *Log->GetListOfLog())
		{
			FString Info = FString(ErrorMessage.Message.c_str());
			AddInfo(Info);
		}
	}
	TestFalse("Compile Success", CompileSuccess);

	const bool RunSuccess = compiler->Run(WeakLog);
	TestFalse("Run Success", RunSuccess);

	const bool IsHeFinished = controller->GetWorld()->IsPlayerFinished();
	TestFalse("Player Shouldn't Be On Finish", IsHeFinished);
	
	return true;
}

bool FExpectWhileErrors::RunTest(const FString& Parameters)
{
	const FString PathToJson = UKismetSystemLibrary::GetProjectDirectory() + "Alpinist/Levels/Tests/ToBeFailedTestsMap.json";
	bool SucceededDeserialize = false;
	
	FString OutInfoMessage;

	const TSharedPtr<FJsonObject> JsonObject = UHelperReaderJsonForAlpinist::ReadJson(PathToJson, SucceededDeserialize, OutInfoMessage);
	TestTrue(OutInfoMessage, SucceededDeserialize);
	
	TArray<FString> Map;
	TestTrue("Not Array", JsonObject->TryGetStringArrayField("game_map", Map));

	const std::vector<std::string> TestMap = CampusUtils::TArrayOfStringToVectorOfString(Map);

	TSharedPtr<AlpinistGame::GameController> controller = MakeShared<AlpinistGame::GameController>(TestMap);
	
	// Check that NotEnd shouldn't use negate---------------------------------------------------------------------------
	TSharedPtr<AlpinistGame::Compiler> compilerNotEnd = MakeShared<AlpinistGame::Compiler>(controller, ".-. ... -..- . -.- -");

	TSharedPtr<AlpinistGame::AlpinistLog> LogNotEnd = MakeShared<AlpinistGame::AlpinistLog>();
	TWeakPtr<AlpinistGame::AlpinistLog> WeakLogNotEnd = LogNotEnd.ToWeakPtr();
	bool CompileSuccess = compilerNotEnd->Compile(WeakLogNotEnd);

	FString ExpectedErrorMessage = "Keyword \"NotEnd\" doesn't expect negating...";
	bool ErrorMessageIsCorrect = false;
	if (!CompileSuccess)
	{
		for (const AlpinistGame::MessageLog ErrorMessage : *LogNotEnd->GetListOfLog())
		{
			const FString Info = FString(ErrorMessage.Message.c_str());
			if (Info == ExpectedErrorMessage)
			{
				ErrorMessageIsCorrect = true;
			}
			AddInfo(Info);
		}
	}
	TestFalse("Compile Success", CompileSuccess);
	TestTrue("NotEnd Error Message Isn't Correct", ErrorMessageIsCorrect);
	
	// Check that while expects ConditionCommand------------------------------------------------------------------------
	TSharedPtr<AlpinistGame::Compiler> compilerConditionCommand = MakeShared<AlpinistGame::Compiler>(controller, ".-. -. . -.- -");
	
	TSharedPtr<AlpinistGame::AlpinistLog> LogConditionCommand = MakeShared<AlpinistGame::AlpinistLog>();
	TWeakPtr<AlpinistGame::AlpinistLog> WeakLogConditionCommand = LogConditionCommand.ToWeakPtr();
	CompileSuccess = compilerConditionCommand->Compile(WeakLogConditionCommand);

	ExpectedErrorMessage = "while expects ConditionCommand...";
	ErrorMessageIsCorrect = false;
	if (!CompileSuccess)
	{
		for (const AlpinistGame::MessageLog ErrorMessage : *LogConditionCommand->GetListOfLog())
		{
			const FString Info = FString(ErrorMessage.Message.c_str());
			if (Info == ExpectedErrorMessage)
			{
				ErrorMessageIsCorrect = true;
			}
			AddInfo(Info);
		}
	}
	TestFalse("Compile Success", CompileSuccess);
	TestTrue("while expects ConditionCommand Error Message Isn't Correct", ErrorMessageIsCorrect);

	// Check that while expects BeginCommand----------------------------------------------------------------------------
	TSharedPtr<AlpinistGame::Compiler> compilerBeginCommand = MakeShared<AlpinistGame::Compiler>(controller, ".-. ... --- .- -");
	
	TSharedPtr<AlpinistGame::AlpinistLog> LogBeginCommand = MakeShared<AlpinistGame::AlpinistLog>();
	TWeakPtr<AlpinistGame::AlpinistLog> WeakLogBeginCommand = LogBeginCommand.ToWeakPtr();
	CompileSuccess = compilerBeginCommand->Compile(WeakLogBeginCommand);

	ExpectedErrorMessage = "While/IfCommand hasn't Scope...";
	ErrorMessageIsCorrect = false;
	if (!CompileSuccess)
	{
		for (const AlpinistGame::MessageLog ErrorMessage : *LogBeginCommand->GetListOfLog())
		{
			const FString Info = FString(ErrorMessage.Message.c_str());
			if (Info == ExpectedErrorMessage)
			{
				ErrorMessageIsCorrect = true;
			}
			AddInfo(Info);
		}
	}
	TestFalse("Compile Success", CompileSuccess);
	TestTrue("while expects BeginCommand Error Message Isn't Correct", ErrorMessageIsCorrect);

	// Check that while expects EndCommand------------------------------------------------------------------------------
	TSharedPtr<AlpinistGame::Compiler> compilerEndCommand = MakeShared<AlpinistGame::Compiler>(controller, ".-. ... --- . .-");
	
	TSharedPtr<AlpinistGame::AlpinistLog> LogEndCommand = MakeShared<AlpinistGame::AlpinistLog>();
	TWeakPtr<AlpinistGame::AlpinistLog> WeakLogEndCommand = LogEndCommand.ToWeakPtr();
	CompileSuccess = compilerEndCommand->Compile(WeakLogEndCommand);

	ExpectedErrorMessage = "While/IfCommand hasn't Scope...";
	ErrorMessageIsCorrect = false;
	if (!CompileSuccess)
	{
		for (const AlpinistGame::MessageLog ErrorMessage : *LogBeginCommand->GetListOfLog())
		{
			const FString Info = FString(ErrorMessage.Message.c_str());
			if (Info == ExpectedErrorMessage)
			{
				ErrorMessageIsCorrect = true;
			}
			AddInfo(Info);
		}
	}
	TestFalse("Compile Success", CompileSuccess);
	TestTrue("while expects EndCommand Error Message Isn't Correct", ErrorMessageIsCorrect);

	return true;
}

bool FExpectIfElseErrors::RunTest(const FString& Parameters)
{
	const FString PathToJson = UKismetSystemLibrary::GetProjectDirectory() + "Alpinist/Levels/Tests/ToBeFailedTestsMap.json";
	bool SucceededDeserialize = false;
	
	FString OutInfoMessage;

	const TSharedPtr<FJsonObject> JsonObject = UHelperReaderJsonForAlpinist::ReadJson(PathToJson, SucceededDeserialize, OutInfoMessage);
	TestTrue(OutInfoMessage, SucceededDeserialize);
	
	TArray<FString> Map;
	TestTrue("Not Array", JsonObject->TryGetStringArrayField("game_map", Map));

	const std::vector<std::string> TestMap = CampusUtils::TArrayOfStringToVectorOfString(Map);

	TSharedPtr<AlpinistGame::GameController> controller = MakeShared<AlpinistGame::GameController>(TestMap);

	// Check that NotEnd shouldn't use with IfElse----------------------------------------------------------------------
	TSharedPtr<AlpinistGame::Compiler> compilerNotEnd = MakeShared<AlpinistGame::Compiler>(controller, ".. -..- . -.- -");

	TSharedPtr<AlpinistGame::AlpinistLog> LogNotEnd = MakeShared<AlpinistGame::AlpinistLog>();
	TWeakPtr<AlpinistGame::AlpinistLog> WeakLogNotEnd = LogNotEnd.ToWeakPtr();
	bool CompileSuccess = compilerNotEnd->Compile(WeakLogNotEnd);

	FString ExpectedErrorMessage = "Can't create IfCommand...";
	bool ErrorMessageIsCorrect = false;
	if (!CompileSuccess)
	{
		for (const AlpinistGame::MessageLog ErrorMessage : *LogNotEnd->GetListOfLog())
		{
			const FString Info = FString(ErrorMessage.Message.c_str());
			if (Info == ExpectedErrorMessage)
			{
				ErrorMessageIsCorrect = true;
			}
			AddInfo(Info);
		}
	}
	TestFalse("Compile Success", CompileSuccess);
	TestTrue("NotEnd Error Message Isn't Correct", ErrorMessageIsCorrect);
	
	// Check that if expects ConditionCommand---------------------------------------------------------------------------
	TSharedPtr<AlpinistGame::Compiler> compilerConditionCommand = MakeShared<AlpinistGame::Compiler>(controller, ".. -. . -.- -");
	
	TSharedPtr<AlpinistGame::AlpinistLog> LogConditionCommand = MakeShared<AlpinistGame::AlpinistLog>();
	TWeakPtr<AlpinistGame::AlpinistLog> WeakLogConditionCommand = LogConditionCommand.ToWeakPtr();
	CompileSuccess = compilerConditionCommand->Compile(WeakLogConditionCommand);

	ExpectedErrorMessage = "if expects ConditionCommand...";
	ErrorMessageIsCorrect = false;
	if (!CompileSuccess)
	{
		for (const AlpinistGame::MessageLog ErrorMessage : *LogConditionCommand->GetListOfLog())
		{
			const FString Info = FString(ErrorMessage.Message.c_str());
			if (Info == ExpectedErrorMessage)
			{
				ErrorMessageIsCorrect = true;
			}
			AddInfo(Info);
		}
	}
	TestFalse("Compile Success", CompileSuccess);
	TestTrue("if expects ConditionCommand Error Message Isn't Correct", ErrorMessageIsCorrect);

	// Check that if/else expects BeginCommand---------------------------------------------------------------------------
	TSharedPtr<AlpinistGame::Compiler> compilerBeginCommand = MakeShared<AlpinistGame::Compiler>(controller, ".. --. -. - -- . .- -");
	
	TSharedPtr<AlpinistGame::AlpinistLog> LogBeginCommand = MakeShared<AlpinistGame::AlpinistLog>();
	TWeakPtr<AlpinistGame::AlpinistLog> WeakLogBeginCommand = LogBeginCommand.ToWeakPtr();
	CompileSuccess = compilerBeginCommand->Compile(WeakLogBeginCommand);

	ExpectedErrorMessage = "While/IfCommand hasn't Scope...";
	ErrorMessageIsCorrect = false;
	if (!CompileSuccess)
	{
		for (const AlpinistGame::MessageLog ErrorMessage : *LogBeginCommand->GetListOfLog())
		{
			const FString Info = FString(ErrorMessage.Message.c_str());
			if (Info == ExpectedErrorMessage)
			{
				ErrorMessageIsCorrect = true;
			}
			AddInfo(Info);
		}
	}
	TestFalse("Compile Success", CompileSuccess);
	TestTrue("if expects BeginCommand Error Message Isn't Correct", ErrorMessageIsCorrect);

	// Check that if/else expects EndCommand----------------------------------------------------------------------------
	TSharedPtr<AlpinistGame::Compiler> compilerEndCommand = MakeShared<AlpinistGame::Compiler>(controller, ".. . -. .-. ... --- . -.- -");
	
	TSharedPtr<AlpinistGame::AlpinistLog> LogEndCommand = MakeShared<AlpinistGame::AlpinistLog>();
	TWeakPtr<AlpinistGame::AlpinistLog> WeakLogEndCommand = LogEndCommand.ToWeakPtr();
	CompileSuccess = compilerEndCommand->Compile(WeakLogEndCommand);

	ExpectedErrorMessage = "While/IfCommand hasn't Scope...";
	ErrorMessageIsCorrect = false;
	if (!CompileSuccess)
	{
		for (const AlpinistGame::MessageLog ErrorMessage : *LogBeginCommand->GetListOfLog())
		{
			const FString Info = FString(ErrorMessage.Message.c_str());
			if (Info == ExpectedErrorMessage)
			{
				ErrorMessageIsCorrect = true;
			}
			AddInfo(Info);
		}
	}
	TestFalse("Compile Success", CompileSuccess);
	TestTrue("if expects EndCommand Error Message Isn't Correct", ErrorMessageIsCorrect);

	// Check that else can't be created without ifCommand---------------------------------------------------------------
	TSharedPtr<AlpinistGame::Compiler> compilerElse = MakeShared<AlpinistGame::Compiler>(controller, "-- . -. .-. ... --- . -.- -");
	
	TSharedPtr<AlpinistGame::AlpinistLog> LogElse = MakeShared<AlpinistGame::AlpinistLog>();
	TWeakPtr<AlpinistGame::AlpinistLog> WeakLogElse = LogElse.ToWeakPtr();
	CompileSuccess = compilerElse->Compile(WeakLogElse);

	ExpectedErrorMessage = "Incorrect IfElseConditional...";
	ErrorMessageIsCorrect = false;
	if (!CompileSuccess)
	{
		for (const AlpinistGame::MessageLog ErrorMessage : *LogBeginCommand->GetListOfLog())
		{
			const FString Info = FString(ErrorMessage.Message.c_str());
			if (Info == ExpectedErrorMessage)
			{
				ErrorMessageIsCorrect = true;
			}
			AddInfo(Info);
		}
	}
	TestFalse("Compile Success", CompileSuccess);
	TestTrue("if expects EndCommand Error Message Isn't Correct", ErrorMessageIsCorrect);

	return true;
}

bool FExpectInfiniteCycleError::RunTest(const FString& Parameters)
{
	const FString PathToJson = UKismetSystemLibrary::GetProjectDirectory() + "Alpinist/Levels/Tests/ToBeFailedTestsMap.json";
	bool SucceededDeserialize = false;
	
	FString OutInfoMessage;

	const TSharedPtr<FJsonObject> JsonObject = UHelperReaderJsonForAlpinist::ReadJson(PathToJson, SucceededDeserialize, OutInfoMessage);
	TestTrue(OutInfoMessage, SucceededDeserialize);
	
	TArray<FString> Map;
	TestTrue("Not Array", JsonObject->TryGetStringArrayField("game_map", Map));

	const std::vector<std::string> TestMap = CampusUtils::TArrayOfStringToVectorOfString(Map);

	TSharedPtr<AlpinistGame::GameController> controller = MakeShared<AlpinistGame::GameController>(TestMap);
	
	TSharedPtr<AlpinistGame::Compiler> compiler = MakeShared<AlpinistGame::Compiler>(controller, ".-. -..- . .- -");

	TSharedPtr<AlpinistGame::AlpinistLog> Log = MakeShared<AlpinistGame::AlpinistLog>();
	TWeakPtr<AlpinistGame::AlpinistLog> WeakLog = Log.ToWeakPtr();

	const bool RunSuccess = compiler->Run(WeakLog);
	TestFalse("Run Success", RunSuccess);

	const bool IsHeFinished = controller->GetWorld()->IsPlayerFinished();
	TestFalse("Player Shouldn't Be On Finish", IsHeFinished);
	
	return true;
}

#endif
#endif
