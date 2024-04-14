// Fill out your copyright notice in the Description page of Project Settings.


#include "HTTPAiMyLogicRequestsLib.h"

#include "HttpModule.h"
#include "Campus/Libraries/Requests/GameAPI/HTTPGameAPIRequestsLib.h"
#include "Interfaces/IHttpResponse.h"
#include "GenericPlatform/GenericPlatformHttp.h"
DEFINE_LOG_CATEGORY(LogRequests);


void UHTTPAiMyLogicRequestsLib::AIMyLogicGetRequest(
	TFunction<void(const FString&, const FString&, const int&)> CallBack, const FString& StringRequest,
	const FString& URL)
{
	FHttpModule* Module = &FHttpModule::Get();
	TSharedPtr<IHttpRequest,ESPMode::ThreadSafe> Request = Module->CreateRequest();
	
	Request->OnProcessRequestComplete().BindLambda(
		[CallBack](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
		{
			UE_LOG(HTTPGameApiLog, Warning, TEXT("%i"), Response->GetResponseCode());
			if(Response->GetResponseCode() == 200)
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

					if (FJsonSerializer::Deserialize(AnswerReader, JsonObjectAnswer))
					{
						UE_LOG(HTTPGameApiLog, Warning, TEXT("Выйграли с дересеариазиц"));
						FString Message = JsonObjectAnswer->GetStringField("message");
						FString ActionType = JsonObjectAnswer->GetStringField("actionType");
						int ActionID = JsonObjectAnswer->GetIntegerField("actionID");

						//UE_LOG(LogRequests, Log, TEXT("GET Request Result: %d"), static_cast<int>(ActionID));
						CallBack(Message, ActionType, ActionID);
					}
					else
					{
						UE_LOG(HTTPGameApiLog, Warning, TEXT("Проебали с дересеариазиц"));
					}
				}
				else
				{
					UE_LOG(HTTPGameApiLog, Warning, TEXT("Invalid"));
				}
			}
			return;
		});
	FString EncodedStringRequest = FGenericPlatformHttp::UrlEncode(StringRequest);
	
	FString FULL_URL = URL + "&query=" + EncodedStringRequest;
	Request->SetURL(FULL_URL);
	Request->SetVerb(TEXT("GET"));
	Request->SetHeader(TEXT("Content-Type"),TEXT("application/json"));
	Request->ProcessRequest();
}

void UHTTPAiMyLogicRequestsLib::CreateGameWithAI(TFunction<void(const FString&)> CallBack, bool StartWithWhite)
{
	TSharedRef<IHttpRequest> Request = FHttpModule::Get().CreateRequest();
	Request->SetURL(TEXT("http://127.0.0.1:5000/create_game"));
	Request->SetVerb(TEXT("POST"));

	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

	Request->SetContentAsString(StartWithWhite ? "{\"player_color\": \"white\"}" : "{\"player_color\": \"black\"}");


	Request->OnProcessRequestComplete().BindLambda(
		[=](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
		{
			if (bConnectedSuccessfully && Response.IsValid())
			{
				int32 StatusCode = Response->GetResponseCode();
				FString ResponseContent = Response->GetContentAsString();
				
				if (StatusCode == 200)
				{
					UE_LOG(LogTemp, Warning, TEXT("Игра создана успешно: %s"), *ResponseContent);

					TSharedPtr<FJsonObject> JsonObject;
					TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseContent);

					if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
					{
						if (JsonObject->HasField("game_id"))
						{
							FString GameID = JsonObject->GetStringField("game_id");
							CallBack(GameID); 
						}
					}
				}
				else
				{
					UE_LOG(LogTemp, Error, TEXT("Ошибка при создании игры. Код ошибки: %d"), StatusCode);
				}
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Ошибка при выполнении HTTP-запроса"));
			}
		});
	Request->ProcessRequest();
}

void UHTTPAiMyLogicRequestsLib::MakeMove(TFunction<void(bool, const FString&, const FString&, const FString&)> CallBack,
										 const FString& GameId, const FString& Move)
{
	TSharedRef<IHttpRequest> Request = FHttpModule::Get().CreateRequest();
	Request->SetURL(TEXT("http://127.0.0.1:5000/make_move"));
	Request->SetVerb(TEXT("POST"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

	FString JsonPayload = FString::Printf(TEXT("{\"game_id\": \"%s\",\"move\": \"%s\"}"), *GameId, *Move);
	UE_LOG(LogTemp, Warning, TEXT("Данные для отправки: %s"), *JsonPayload);
	Request->SetContentAsString(JsonPayload);

	Request->OnProcessRequestComplete().BindLambda(
		[=](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
		{
			if (bConnectedSuccessfully && Response.IsValid())
			{
				int32 StatusCode = Response->GetResponseCode();
				FString ResponseContent = Response->GetContentAsString();
				
				TSharedPtr<FJsonObject> JsonObject;
				TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseContent);
				
				UE_LOG(LogRequests, Warning, TEXT("%s"), *ResponseContent)
				if (StatusCode == 200)
				{
					if (FJsonSerializer::Deserialize(Reader, JsonObject))
					{
						UE_LOG(LogTemp, Warning, TEXT("Ход выполнен успешно: %s"), *ResponseContent);

						bool bValidMove = JsonObject->GetBoolField("valid_move");
						FString PlayerCastle = JsonObject->GetStringField("player_castle");
						FString GameStatus = JsonObject->GetStringField("game_status");
						FString CurrentFen = JsonObject->GetStringField("current_fen");
 
						CallBack(bValidMove, PlayerCastle, GameStatus, CurrentFen);
					}
					else
					{
						UE_LOG(LogTemp, Error, TEXT("Ошибка при выполнении хода. Код ошибки: %d"), StatusCode);
					}
				}
				else
				{
					UE_LOG(LogTemp, Error, TEXT("Ошибка при выполнении HTTP-запроса"));
				}
			}
		}
			);
	Request->ProcessRequest();
}

void UHTTPAiMyLogicRequestsLib::MakeAiMove(TFunction<void(const FString&, const FString&, const FString&, const FString&)> CallBack, const FString& GameId)
{
	TSharedRef<IHttpRequest> Request = FHttpModule::Get().CreateRequest();
	Request->SetURL(TEXT("http://127.0.0.1:5000/make_ai_move"));
	Request->SetVerb(TEXT("POST"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

	FString JsonPayload = FString::Printf(TEXT("{\"game_id\": \"%s\"}"), *GameId);
	
	Request->SetContentAsString(JsonPayload);

	Request->OnProcessRequestComplete().BindLambda(
		[=](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
		{
			if (bConnectedSuccessfully && Response.IsValid())
			{
				int32 StatusCode = Response->GetResponseCode();
				FString ResponseContent = Response->GetContentAsString();
				
				TSharedPtr<FJsonObject> JsonObject;
				TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseContent);
				
				UE_LOG(LogRequests, Warning, TEXT("%s"), *ResponseContent)
				if (StatusCode == 200)
				{
					if (FJsonSerializer::Deserialize(Reader, JsonObject))
					{

						UE_LOG(LogTemp, Warning, TEXT("Ход выполнен успешно: %s"), *ResponseContent);

						const FString& AIMove = JsonObject->GetStringField("ai_move");
						const FString& AICastle = JsonObject->GetStringField("ai_castle");
						const FString& GameStatus = JsonObject->GetStringField("game_status");
						const FString& CurrentFen = JsonObject->GetStringField("current_fen");
						
						CallBack(AIMove, AICastle, GameStatus, CurrentFen);
					}
					else
					{
						UE_LOG(LogTemp, Error, TEXT("Ошибка при выполнении хода. Код ошибки: %d"), StatusCode);
					}
				}
				else
				{
					UE_LOG(LogTemp, Error, TEXT("Ошибка при выполнении HTTP-запроса"));
				}
			}
		}
			);
	Request->ProcessRequest();
}
