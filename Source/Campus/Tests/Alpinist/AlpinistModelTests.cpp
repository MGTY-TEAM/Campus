#if WITH_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"
#include "Dom/JsonObject.h"
#include "Campus/Libraries/CampusUtils.h"

#include "Campus/MiniGames/Alpinist/Core/AlpinistLanguage/Compiler.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FCorrectUsingJsonMaps, "Campus.Alpinist.CorrectUsingJsonMaps",
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

bool FCorrectUsingJsonMaps::RunTest(const FString& Parameters)
{
	const FString PathToJson = "D:/A_Repositories/Campus/Alpinist/Levels/BigMapTest.json";
	bool SucceededDeserialize = false;
	FString OutInfoMessage;

	const TSharedPtr<FJsonObject> JsonObject = ReadJson(PathToJson, SucceededDeserialize, OutInfoMessage);
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

	AlpinistGame::GameController* controller = new AlpinistGame::GameController(TestMap);
	
	AlpinistGame::Compiler* compiler = new AlpinistGame::Compiler(controller, "-. -. .-. --. . -.- - .. --- . -. - .-. ... --- . -.- - -. .-. ... --. . -.- - .- -.-");
	TestTrue("Compile Fail", compiler->Run());

	const bool IsHeFinished = controller->GetWorld()->IsPlayerFinished();
	TestTrue("Player Should Be On Finish", IsHeFinished);
	
	return true;
}

#endif