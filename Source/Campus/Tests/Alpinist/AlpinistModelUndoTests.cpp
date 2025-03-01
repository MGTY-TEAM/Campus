#include "Misc/AutomationTest.h"

#ifdef ALPINIST_GAME
#if WITH_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"
#include "Dom/JsonObject.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UHelperReaderJsonForAlpinist.h"
#include "Campus/Libraries/CampusUtils.h"
#include "Campus/MiniGames/Alpinist/Core/Commands.h"
#include "Campus/MiniGames/Alpinist/Core/Entities.h"
#include "Campus/MiniGames/Alpinist/Core/GameController.h"
#include "Campus/MiniGames/Alpinist/Core/AlpinistLanguage/Compiler.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FExpectUndoCommands, "Campus.Alpinist.ExpectUndoCommands",
								EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)

bool FExpectUndoCommands::RunTest(const FString& Parameters)
{
	const FString PathToJson = UKismetSystemLibrary::GetProjectDirectory() + "Alpinist/Levels/Tests/ToBeFailedTestsMap.json";
	bool SucceededDeserialize = false;
	
	FString OutInfoMessage;

	const TSharedPtr<FJsonObject> JsonObject = UHelperReaderJsonForAlpinist::ReadJson(PathToJson, SucceededDeserialize, OutInfoMessage);
	TestTrue(OutInfoMessage, SucceededDeserialize);
	
	TArray<FString> Map;
	TestTrue("Not Array", JsonObject->TryGetStringArrayField("game_map", Map));

	AddInfo("Startup-Map-------------------------------------");
	for (const FString& Str : Map)
	{
		AddInfo(Str);
	}
	AddInfo("------------------------------------------------");

	const std::vector<std::string> TestMap = CampusUtils::TArrayOfStringToVectorOfString(Map);

	TSharedPtr<AlpinistGame::GameController> controller = MakeShared<AlpinistGame::GameController>(TestMap);
	
	TSharedPtr<AlpinistGame::Compiler> compiler = MakeShared<AlpinistGame::Compiler>(controller, "-.- -.- .- -.- -.-");

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
	TestTrue("Compile Fail", CompileSuccess);

	const TSharedPtr<AlpinistGame::MacroCommand> Commands = compiler->GetListOfCommands();
	TestNotNull("Commands is nullptr", Commands.Get());
	
	const std::list<TSharedPtr<AlpinistGame::PlayerCommand>> m_commandList = Commands->GetList();
	TestNotNull("0 item of m_commandList is nullptr", m_commandList.front().Get());

	const std::pair<int8_t, int8_t> StartedPos = controller->GetWorld()->GetPlayer()->GetPos();
	auto FirstIt = m_commandList.begin();
	const auto FirstCommand = *FirstIt;
	FirstCommand->Execute(WeakLog);
	std::pair<int8_t, int8_t> CurrentPos = controller->GetWorld()->GetPlayer()->GetPos();
	TestTrue("Expected Move Command UP first", (StartedPos.first - 1) == CurrentPos.first && StartedPos.second == CurrentPos.second);

	auto SecondIt = ++FirstIt;
	const auto SecondCommand = *SecondIt;
	TestNotNull("1 item of m_commandList is nullptr", SecondCommand.Get());
	SecondCommand->Execute(WeakLog);
	CurrentPos = controller->GetWorld()->GetPlayer()->GetPos();
	TestTrue("Expected Move Command UP second", (StartedPos.first - 2) == CurrentPos.first && StartedPos.second == CurrentPos.second);

	SecondCommand->Unexecute();
	CurrentPos = controller->GetWorld()->GetPlayer()->GetPos();
	TestTrue("Expected UNEXECUTE Move Command UP second", (StartedPos.first - 1) == CurrentPos.first && StartedPos.second == CurrentPos.second);

	SecondCommand->Unexecute();
	CurrentPos = controller->GetWorld()->GetPlayer()->GetPos();
	TestTrue("Expected UNEXECUTE Move Command UP second", (StartedPos.first - 1) == CurrentPos.first && StartedPos.second == CurrentPos.second);
	
	FirstCommand->Unexecute();
	CurrentPos = controller->GetWorld()->GetPlayer()->GetPos();
	TestTrue("Expected UNEXECUTE Move Command UP first", StartedPos.first == CurrentPos.first && StartedPos.second == CurrentPos.second);

	FirstCommand->Execute(WeakLog);
	SecondCommand->Execute(WeakLog);

	auto ThirdIt = ++SecondIt;
	const auto ThirdCommand = *ThirdIt;
	TestNotNull("2 item of m_commandList is nullptr", ThirdCommand.Get());
	ThirdCommand->Execute(WeakLog);
	CurrentPos = controller->GetWorld()->GetPlayer()->GetPos();
	TestTrue("Expected Right Command", (StartedPos.first - 2) == CurrentPos.first && StartedPos.second == CurrentPos.second);

	auto FourthIt = ++ThirdIt;
	const auto FourthCommand = *FourthIt;
	TestNotNull("3 item of m_commandList is nullptr", FourthCommand.Get());
	FourthCommand->Execute(WeakLog);
	CurrentPos = controller->GetWorld()->GetPlayer()->GetPos();
	TestTrue("Expected Move Command RIGHT first", (StartedPos.first - 2) == CurrentPos.first && (StartedPos.second + 1) == CurrentPos.second);

	const auto FifthIt = ++FourthIt;
	const auto FifthCommand = *FifthIt;
	TestNotNull("4 item of m_commandList is nullptr", FifthCommand.Get());
	FifthCommand->Execute(WeakLog);
	CurrentPos = controller->GetWorld()->GetPlayer()->GetPos();
	TestTrue("Expected Move Command RIGHT second", (StartedPos.first - 2) == CurrentPos.first && (StartedPos.second + 2) == CurrentPos.second);
	
	bool IsHeFinished = controller->GetWorld()->IsPlayerFinished();
	TestTrue("Player Should Be On Finish", IsHeFinished);
	
	FifthCommand->Unexecute();
	CurrentPos = controller->GetWorld()->GetPlayer()->GetPos();
	TestTrue("Expected UNEXECUTE Move Command RIGHT first", (StartedPos.first - 2) == CurrentPos.first && (StartedPos.second + 1) == CurrentPos.second);

	IsHeFinished = controller->GetWorld()->IsPlayerFinished();
	TestFalse("Player Shouldn't Be On Finish", IsHeFinished);

	FifthCommand->Execute(WeakLog);
	IsHeFinished = controller->GetWorld()->IsPlayerFinished();
	TestTrue("Player Should Be On Finish", IsHeFinished);
	
	FifthCommand->Unexecute();
	FourthCommand->Unexecute();
	ThirdCommand->Unexecute();
	SecondCommand->Unexecute();
	FirstCommand->Unexecute();
	CurrentPos = controller->GetWorld()->GetPlayer()->GetPos();
	
	TestTrue("Expected UNEXECUTE Move Command UP second", StartedPos.first == CurrentPos.first && StartedPos.second == CurrentPos.second);
	
	return true;
}

#endif
#endif
