#pragma once

#include "Dom/JsonObject.h"

class UHelperReaderJsonForAlpinist
{
public:
	static FString ReadStringFromFile(const FString& FilePath, bool& bOutSuccess, FString& OutInfoMessage)
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
	
	static TSharedPtr<FJsonObject> ReadJson(const FString& JsonFilePath, bool& bOutSuccess, FString& OutInfoMessage)
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
};
