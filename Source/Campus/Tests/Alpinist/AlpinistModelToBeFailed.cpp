#ifdef ALPINIST_GAME
#if WITH_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"
#include "Dom/JsonObject.h"
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

namespace
{
	FString ReadStringFromFile(const FString& FilePath, bool& bOutSuccess, FString& OutInfoMessage)
	{
		if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*FilePath))
		{
			bOutSuccess = false;
			OutInfoMessage = FString::Printf(TEXT("Read String From file Failed - File doesn't exists - '%s'"), *FilePath);
			return "";
		}

		FString RetString = "";

		if (!FFileHelper::LoadFileToString(RetString, *FilePath))
		{
			bOutSuccess = false;
			OutInfoMessage = FString::Printf(TEXT("Read String From file Failed - Was not able to read file. - '%s'"), *FilePath);
			return "";
		}

		bOutSuccess = true;
		OutInfoMessage = FString::Printf(TEXT("Read String From file Successed. - '%s'"), *FilePath);
		return RetString;
	}
	
	TSharedPtr<FJsonObject> ReadJson(const FString& JsonFilePath, bool& bOutSuccess, FString& OutInfoMessage)
	{
		const FString JsonString = ReadStringFromFile(JsonFilePath, bOutSuccess, OutInfoMessage);
		if (!bOutSuccess)
		{
			return nullptr;
		}

		TSharedPtr<FJsonObject> RetJsonObject;

		if (!FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(JsonString),RetJsonObject))
		{
			bOutSuccess = false;
			OutInfoMessage = FString::Printf(TEXT("Read Json Failed - Was not able to deserialize the json sting. - '%s'"), *JsonString);
			return nullptr;
		}

		bOutSuccess = true;
		OutInfoMessage = FString::Printf(TEXT("Read Json Succeeded. - '%s'"), *JsonFilePath);
		return RetJsonObject;
	}
}

bool FExpectLexerErrors::RunTest(const FString& Parameters)
{
	const FString PathToJson = "D:/A_Repositories/Campus/Alpinist/Levels/ToBeFailedTestsMap.json";
	bool SucceededDeserialize = false;
	
	FString OutInfoMessage;

	const TSharedPtr<FJsonObject> JsonObject = ReadJson(PathToJson, SucceededDeserialize, OutInfoMessage);
	TestTrue(OutInfoMessage, SucceededDeserialize);
	
	TArray<FString> Map;
	TestTrue("Not Array", JsonObject->TryGetStringArrayField("game_map", Map));

	const std::vector<std::string> TestMap = CampusUtils::TArrayOfStringToVectorOfString(Map);

	AlpinistGame::GameController* controller = new AlpinistGame::GameController(TestMap);
	
	AlpinistGame::Compiler* compiler = new AlpinistGame::Compiler(controller, "--.-.-");

	AlpinistGame::AlpinistLog Log;
	const bool CompileSuccess = compiler->Compile(Log);
	if (!CompileSuccess)
	{
		for (const AlpinistGame::MessageLog ErrorMessage : *Log.GetListOfLog())
		{
			FString Info = FString(ErrorMessage.Message.c_str());
			AddInfo(Info);
		}
	}
	TestFalse("Compile Success", CompileSuccess);

	const bool RunSuccess = compiler->Run(Log);
	TestFalse("Run Success", RunSuccess);

	const bool IsHeFinished = controller->GetWorld()->IsPlayerFinished();
	TestFalse("Player Shouldn't Be On Finish", IsHeFinished);
	
	return true;
}

bool FExpectWhileErrors::RunTest(const FString& Parameters)
{
	const FString PathToJson = "D:/A_Repositories/Campus/Alpinist/Levels/ToBeFailedTestsMap.json";
	bool SucceededDeserialize = false;
	
	FString OutInfoMessage;

	const TSharedPtr<FJsonObject> JsonObject = ReadJson(PathToJson, SucceededDeserialize, OutInfoMessage);
	TestTrue(OutInfoMessage, SucceededDeserialize);
	
	TArray<FString> Map;
	TestTrue("Not Array", JsonObject->TryGetStringArrayField("game_map", Map));

	const std::vector<std::string> TestMap = CampusUtils::TArrayOfStringToVectorOfString(Map);

	AlpinistGame::GameController* controller = new AlpinistGame::GameController(TestMap);

	// Check that NotEnd shouldn't use negate---------------------------------------------------------------------------
	AlpinistGame::Compiler* compilerNotEnd = new AlpinistGame::Compiler(controller, ".-. ... -..- . -.- -");

	AlpinistGame::AlpinistLog LogNotEnd;
	bool CompileSuccess = compilerNotEnd->Compile(LogNotEnd);

	FString ExpectedErrorMessage = "Keyword \"NotEnd\" doesn't expect negating...";
	bool ErrorMessageIsCorrect = false;
	if (!CompileSuccess)
	{
		for (const AlpinistGame::MessageLog ErrorMessage : *LogNotEnd.GetListOfLog())
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
	AlpinistGame::Compiler* compilerConditionCommand = new AlpinistGame::Compiler(controller, ".-. -. . -.- -");
	AlpinistGame::AlpinistLog LogConditionCommand;
	CompileSuccess = compilerConditionCommand->Compile(LogConditionCommand);

	ExpectedErrorMessage = "while expects ConditionCommand.";
	ErrorMessageIsCorrect = false;
	if (!CompileSuccess)
	{
		for (const AlpinistGame::MessageLog ErrorMessage : *LogConditionCommand.GetListOfLog())
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
	AlpinistGame::Compiler* compilerBeginCommand = new AlpinistGame::Compiler(controller, ".-. ... --- .- -");
	AlpinistGame::AlpinistLog LogBeginCommand;
	CompileSuccess = compilerBeginCommand->Compile(LogBeginCommand);

	ExpectedErrorMessage = "While/IfCommand hasn't Scope.";
	ErrorMessageIsCorrect = false;
	if (!CompileSuccess)
	{
		for (const AlpinistGame::MessageLog ErrorMessage : *LogBeginCommand.GetListOfLog())
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
	AlpinistGame::Compiler* compilerEndCommand = new AlpinistGame::Compiler(controller, ".-. ... --- . .-");
	AlpinistGame::AlpinistLog LogEndCommand;
	CompileSuccess = compilerEndCommand->Compile(LogEndCommand);

	ExpectedErrorMessage = "While/IfCommand hasn't Scope.";
	ErrorMessageIsCorrect = false;
	if (!CompileSuccess)
	{
		for (const AlpinistGame::MessageLog ErrorMessage : *LogBeginCommand.GetListOfLog())
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
	const FString PathToJson = "D:/A_Repositories/Campus/Alpinist/Levels/ToBeFailedTestsMap.json";
	bool SucceededDeserialize = false;
	
	FString OutInfoMessage;

	const TSharedPtr<FJsonObject> JsonObject = ReadJson(PathToJson, SucceededDeserialize, OutInfoMessage);
	TestTrue(OutInfoMessage, SucceededDeserialize);
	
	TArray<FString> Map;
	TestTrue("Not Array", JsonObject->TryGetStringArrayField("game_map", Map));

	const std::vector<std::string> TestMap = CampusUtils::TArrayOfStringToVectorOfString(Map);

	AlpinistGame::GameController* controller = new AlpinistGame::GameController(TestMap);

	// Check that NotEnd shouldn't use with IfElse----------------------------------------------------------------------
	AlpinistGame::Compiler* compilerNotEnd = new AlpinistGame::Compiler(controller, ".. -..- . -.- -");

	AlpinistGame::AlpinistLog LogNotEnd;
	bool CompileSuccess = compilerNotEnd->Compile(LogNotEnd);

	FString ExpectedErrorMessage = "Can't create IfCommand.";
	bool ErrorMessageIsCorrect = false;
	if (!CompileSuccess)
	{
		for (const AlpinistGame::MessageLog ErrorMessage : *LogNotEnd.GetListOfLog())
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
	AlpinistGame::Compiler* compilerConditionCommand = new AlpinistGame::Compiler(controller, ".. -. . -.- -");
	AlpinistGame::AlpinistLog LogConditionCommand;
	CompileSuccess = compilerConditionCommand->Compile(LogConditionCommand);

	ExpectedErrorMessage = "if expects ConditionCommand.";
	ErrorMessageIsCorrect = false;
	if (!CompileSuccess)
	{
		for (const AlpinistGame::MessageLog ErrorMessage : *LogConditionCommand.GetListOfLog())
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
	AlpinistGame::Compiler* compilerBeginCommand = new AlpinistGame::Compiler(controller, ".. --. -. - -- . .- -");
	AlpinistGame::AlpinistLog LogBeginCommand;
	CompileSuccess = compilerBeginCommand->Compile(LogBeginCommand);

	ExpectedErrorMessage = "While/IfCommand hasn't Scope.";
	ErrorMessageIsCorrect = false;
	if (!CompileSuccess)
	{
		for (const AlpinistGame::MessageLog ErrorMessage : *LogBeginCommand.GetListOfLog())
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
	AlpinistGame::Compiler* compilerEndCommand = new AlpinistGame::Compiler(controller, ".. . -. .-. ... --- . -.- -");
	AlpinistGame::AlpinistLog LogEndCommand;
	CompileSuccess = compilerEndCommand->Compile(LogEndCommand);

	ExpectedErrorMessage = "While/IfCommand hasn't Scope.";
	ErrorMessageIsCorrect = false;
	if (!CompileSuccess)
	{
		for (const AlpinistGame::MessageLog ErrorMessage : *LogBeginCommand.GetListOfLog())
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
	AlpinistGame::Compiler* compilerElse = new AlpinistGame::Compiler(controller, "-- . -. .-. ... --- . -.- -");
	AlpinistGame::AlpinistLog LogElse;
	CompileSuccess = compilerElse->Compile(LogElse);

	ExpectedErrorMessage = "Incorrect IfElseConditional.";
	ErrorMessageIsCorrect = false;
	if (!CompileSuccess)
	{
		for (const AlpinistGame::MessageLog ErrorMessage : *LogBeginCommand.GetListOfLog())
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
	const FString PathToJson = "D:/A_Repositories/Campus/Alpinist/Levels/ToBeFailedTestsMap.json";
	bool SucceededDeserialize = false;
	
	FString OutInfoMessage;

	const TSharedPtr<FJsonObject> JsonObject = ReadJson(PathToJson, SucceededDeserialize, OutInfoMessage);
	TestTrue(OutInfoMessage, SucceededDeserialize);
	
	TArray<FString> Map;
	TestTrue("Not Array", JsonObject->TryGetStringArrayField("game_map", Map));

	const std::vector<std::string> TestMap = CampusUtils::TArrayOfStringToVectorOfString(Map);

	AlpinistGame::GameController* controller = new AlpinistGame::GameController(TestMap);
	
	AlpinistGame::Compiler* compiler = new AlpinistGame::Compiler(controller, ".-. -..- . .- -");

	AlpinistGame::AlpinistLog Log;

	const bool RunSuccess = compiler->Run(Log);
	TestFalse("Run Success", RunSuccess);

	const bool IsHeFinished = controller->GetWorld()->IsPlayerFinished();
	TestFalse("Player Shouldn't Be On Finish", IsHeFinished);
	
	return true;
}

#endif
#endif
