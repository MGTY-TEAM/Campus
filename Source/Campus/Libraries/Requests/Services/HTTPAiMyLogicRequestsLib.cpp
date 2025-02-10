// Fill out your copyright notice in the Description page of Project Settings.


#include "HTTPAiMyLogicRequestsLib.h"

#include "HttpModule.h"
#include "GenericPlatform/GenericPlatformHttp.h"
#include "Interfaces/IHttpResponse.h"

DEFINE_LOG_CATEGORY(LogRequests);

void UHTTPAiMyLogicRequestsLib::AIMyLogicGetRequest(TFunction<void(const FString&, const FString&, const int&)> CallBack, const FString& StringRequest, const FString& URL)
{
	FHttpModule* Module = &FHttpModule::Get();
	auto Request = Module->CreateRequest();
	Request->OnProcessRequestComplete().BindLambda(
		[CallBack](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
		{
			FString YourJsonString = Response->GetContentAsString();
			TSharedPtr<FJsonObject> JsonObject;
			TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(YourJsonString);
			if (FJsonSerializer::Deserialize(Reader, JsonObject))
			{
				TSharedPtr<FJsonObject> DataObject = JsonObject->GetObjectField("data");
				FString Answer = DataObject->GetStringField("answer");

				TSharedPtr<FJsonObject> JsonObjectAnswer;
				TSharedRef<TJsonReader<>> AnswerReader = TJsonReaderFactory<>::Create(Answer);
				
				if(FJsonSerializer::Deserialize(AnswerReader, JsonObjectAnswer))
				{
					FString Message = JsonObjectAnswer-> GetStringField("message");
					FString ActionType = JsonObjectAnswer -> GetStringField("actionType");
					int ActionID = JsonObjectAnswer -> GetIntegerField("actionID");
					
					//UE_LOG(LogRequests, Log, TEXT("GET Request Result: %d"), static_cast<int>(ActionID));
					CallBack(Message, ActionType, ActionID);
				}
				
				//CallBack(Answer, Answer);
			}
		});
	FString EncodedStringRequest = FGenericPlatformHttp::UrlEncode(StringRequest);
	FString FULL_URL = URL + "&query=" + EncodedStringRequest;
	Request->SetURL(FULL_URL);
	Request->SetVerb(TEXT("GET"));
	Request->SetHeader(TEXT("Content-Type"),TEXT("application/json"));
	Request->ProcessRequest();
}

