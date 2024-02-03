// Fill out your copyright notice in the Description page of Project Settings.


#include "HTTPAiMyLogicRequestsLib.h"

#include "HTTPAiMyLogicRequestsLib.h"
#include "HttpModule.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Interfaces/IHttpResponse.h"
#include "GenericPlatform/GenericPlatformHttp.h"
#include "Interfaces/IPv4/IPv4Address.h"
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

void UHTTPAiMyLogicRequestsLib::MakeMove(const FString& GameId, const FString& Move, bool OfferingDraw)
{
	TSharedRef<IHttpRequest> Request = FHttpModule::Get().CreateRequest();
	Request->SetURL(FString::Printf(TEXT("https://lichess.org/api/board/game/%s/move/%s"), *GameId, *Move));
	Request->SetVerb(TEXT("POST"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
    
	// Замените "{ACCESS_TOKEN}" на ваш токен авторизации
	FString AccessToken = "lip_RCA8VdGf766wCcXmUMui";
	Request->SetHeader(TEXT("Authorization"), FString::Printf(TEXT("Bearer %s"), *AccessToken));

	FString JsonPayload = FString::Printf(TEXT("{\"offeringDraw\": %s}"), OfferingDraw ? TEXT("true") : TEXT("false"));
	Request->SetContentAsString(JsonPayload);

	Request->OnProcessRequestComplete().BindLambda([](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
	{
		if (bConnectedSuccessfully && Response.IsValid())
		{
			int32 StatusCode = Response->GetResponseCode();
			FString ResponseContent = Response->GetContentAsString();
			UE_LOG(LogRequests, Warning, TEXT("%s"), *ResponseContent)
			if (StatusCode == 200)
			{
				// Ход успешно выполнен
				UE_LOG(LogTemp, Warning, TEXT("Ход выполнен успешно: %s"), *ResponseContent);
			}
			else
			{
				// Обработка ошибки
				UE_LOG(LogTemp, Error, TEXT("Ошибка при выполнении хода. Код ошибки: %d"), StatusCode);
			}
		}
		else
		{
			// Обработка ошибки запроса
			UE_LOG(LogTemp, Error, TEXT("Ошибка при выполнении HTTP-запроса"));
		}
	});
	Request->ProcessRequest();
}




void UHTTPAiMyLogicRequestsLib::CreateGameWithAI(TFunction<void(const FString&)> CallBack, bool StartWithWhite)
{
	TSharedRef<IHttpRequest> Request = FHttpModule::Get().CreateRequest();
	Request->SetURL(TEXT("http://127.0.0.1:5000/create_game"));
	Request->SetVerb(TEXT("POST"));
	
	Request->SetContentAsString(StartWithWhite ? "{\"player_color\": \"white\"}" : "{\"player_color\": \"black\"}");
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));


	Request->OnProcessRequestComplete().BindLambda([=](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
	{
		if (bConnectedSuccessfully && Response.IsValid())
		{
			int32 StatusCode = Response->GetResponseCode();
			FString ResponseContent = Response->GetContentAsString();
			UE_LOG(LogRequests, Warning, TEXT("%s"), *ResponseContent)
			if (StatusCode == 200)
			{
				UE_LOG(LogTemp, Warning, TEXT("Игра создана успешно: %s"), *ResponseContent);

				TSharedPtr<FJsonObject> JsonObject;
				TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseContent);

				if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
				{
					// Проверьте наличие и правильность ключа в вашем JSON-ответе
					if (JsonObject->HasField("game_id"))
					{
						FString GameID = JsonObject->GetStringField("game_id");
						CallBack(GameID); // Передача ID игры в Callback
					}
				}
			}
			else
			{
				// Обработка ошибки
				UE_LOG(LogTemp, Error, TEXT("Ошибка при создании игры. Код ошибки: %d"), StatusCode);
			}
		}
		else
		{
			// Обработка ошибки запроса
			UE_LOG(LogTemp, Error, TEXT("Ошибка при выполнении HTTP-запроса"));
		}
	});
	Request->ProcessRequest();
}
