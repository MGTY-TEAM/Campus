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

void UHTTPAiMyLogicRequestsLib::MakeMove(const FString& GameId, const FString& Move, bool OfferingDraw)
{
	TSharedRef<IHttpRequest> Request = FHttpModule::Get().CreateRequest();
	Request->SetURL(FString::Printf(TEXT("https://lichess.org/api/board/game/%s/move/%s"), *GameId, *Move));
	Request->SetVerb(TEXT("POST"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
    
	// Замените "{ACCESS_TOKEN}" на ваш токен авторизации
	FString AccessToken = "lip_VZxSCsNUaVSIzRxQlg3f";
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


void UHTTPAiMyLogicRequestsLib::CreateChessGame(FString AccessToken, int32 Level, int32 ClockLimit, int32 ClockIncrement, bool IsRated, FString Color, TFunction<void(bool, FString)> OnCreateGameCompleted)
{
    // Формируем URL для создания партии
    FString URL = "https://lichess.org/api/challenge";

    // Формируем JSON-запрос для создания партии
    TSharedPtr<FJsonObject> RequestData = MakeShareable(new FJsonObject);
    RequestData->SetNumberField("level", Level);

    TSharedPtr<FJsonObject> ClockData = MakeShareable(new FJsonObject);
    ClockData->SetNumberField("limit", ClockLimit);
    ClockData->SetNumberField("increment", ClockIncrement);
    RequestData->SetObjectField("clock", ClockData);

    RequestData->SetBoolField("rated", IsRated);
    RequestData->SetStringField("color", Color);

    FString JsonRequest;
    TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&JsonRequest);
    FJsonSerializer::Serialize(RequestData.ToSharedRef(), JsonWriter);

    // Создаем HTTP-запрос
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = HttpModule->CreateRequest();
    HttpRequest->SetURL(URL);
    HttpRequest->SetVerb("POST");
    HttpRequest->SetHeader("Content-Type", "application/json");
    HttpRequest->SetHeader("Authorization", "Bearer " + AccessToken);
    HttpRequest->SetContentAsString(JsonRequest);

    // Устанавливаем обработчики событий
    HttpRequest->OnProcessRequestComplete().BindLambda(
        [OnCreateGameCompleted](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
        {
            bool bSuccess = false;
            FString Message;

            if (bConnectedSuccessfully && Response.IsValid())
            {
                if (Response->GetResponseCode() == 200)
                {
                    // Обработка успешного ответа
                    bSuccess = true;
                    Message = "Game created successfully";
                }
                else
                {
                    // Обработка ошибочного ответа
                    Message = "Failed to create game";
                }
            }
            else
            {
                // Обработка ошибки подключения
                Message = "Connection error";
            }

            OnCreateGameCompleted(bSuccess, Message);
        }
    );

    // Выполняем запрос
    HttpRequest->ProcessRequest();
}

