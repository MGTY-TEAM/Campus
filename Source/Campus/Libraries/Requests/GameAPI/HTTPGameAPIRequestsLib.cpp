// Fill out your copyright notice in the Description page of Project Settings.


#include "HTTPGameAPIRequestsLib.h"

#include "HTTPGameAPIStructures.h"
#include "HttpModule.h"
#include "HttpRetrySystem.h"
#include "JsonObjectConverter.h"
#include "Interfaces/IHttpResponse.h"


void UHTTPGameAPIRequestsLib::GameAPILoginRequest(
	TFunction<void(const bool&, const FLoginResponse&, const FErrorResponse&)> CallBack,
	const FLoginRequest& LoginRequest)
{
	
	FString URL = "http://localhost:3000/api/login";

	FHttpModule* Module = &FHttpModule::Get();

	TSharedRef<IHttpRequest> Request = Module->CreateRequest();

	Request->OnProcessRequestComplete().BindLambda(
		[=](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
		{
			const int32 ResponseCode = Response->GetResponseCode();
			const FString JsonString = Response->GetContentAsString();
			
			switch (ResponseCode)
			{
			case 200:
				{
					FLoginResponse LoginResponse;
					GetStructFromJsonString(JsonString, LoginResponse);
					UE_LOG(HTTPGameApiLog, Warning, TEXT("Login Response Token: %s"), *LoginResponse.Token);

					CallBack(true, LoginResponse, FErrorResponse());
					break;
				}
			case 400:
				{
					FErrorResponse LoginErrorResponse;
					GetStructFromJsonString(JsonString, LoginErrorResponse);
					UE_LOG(HTTPGameApiLog, Warning, TEXT("Login Error: %s"), *LoginErrorResponse.Error)
					CallBack(false, FLoginResponse(), LoginErrorResponse);
					break;
				}
			default:
					UE_LOG(HTTPGameApiLog, Warning, TEXT("Undefined Response Code: %d"), ResponseCode);
				break;
			}
		});
	
	FString RequestString;
	if (GetJsonStringFromStruct(LoginRequest,RequestString))
	{
		Request->SetURL(URL);
		Request->SetVerb(TEXT("Post"));
		Request->SetHeader(TEXT("Content-Type"),TEXT("application/json"));
		Request->SetHeader(TEXT("Accept"),TEXT("application/json"));
		Request->SetContentAsString(RequestString);
		Request->ProcessRequest();
	}
}

void UHTTPGameAPIRequestsLib::GameAPIRegisterRequest(
	TFunction<void(const bool&, const FRegisterResponse&, const FErrorResponse&)> CallBack,
	const FRegisterRequest& RegisterRequest)
{
	FString URL = "http://localhost:3000/api/register";
	FHttpModule* Module = &FHttpModule::Get();

	TSharedRef<IHttpRequest> Request = Module->CreateRequest();

	Request->OnProcessRequestComplete().BindLambda(
		[CallBack](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
		{
			int32 ResponseCode = Response->GetResponseCode();
			switch (ResponseCode)
			{
			case 200:
				{
					FRegisterResponse RegisterResponse;
					GetStructFromJsonString(Response->GetContentAsString(), RegisterResponse);
					UE_LOG(HTTPGameApiLog, Log, TEXT("Register Response token: %s "), *RegisterResponse.Token);
					CallBack(true, RegisterResponse, FErrorResponse());
				}
				break;
			case 400:
				{
					FErrorResponse ErrorResponse;
					GetStructFromJsonString(Response->GetContentAsString(), ErrorResponse);
					UE_LOG(HTTPGameApiLog, Error, TEXT("Register Error: %s"), *ErrorResponse.Error);
					CallBack(false, FRegisterResponse(), ErrorResponse);
					break;
				}
			default:
				UE_LOG(HTTPGameApiLog, Error, TEXT("Unknown response code: %d"), ResponseCode);
				break;
			}
		});

	FString RequestString;
	if(GetJsonStringFromStruct(RegisterRequest, RequestString))
	{
		Request->SetURL(URL);
		Request->SetVerb(TEXT("Post"));
		Request->SetHeader(TEXT("Content-Type"),TEXT("application/json"));
		Request->SetContentAsString(RequestString);
		Request->ProcessRequest();
	}
}

void UHTTPGameAPIRequestsLib::GameAPIUserInfoRequest(
	TFunction<void(const bool&, const FUserInfoResponse&, const FErrorResponse&)> CallBack,
	const FUserInfoRequest& UserInfoRequest)
{
	FString URL = "http://localhost:3000/api/user-info";
	FHttpModule* Module = &FHttpModule::Get();

	TSharedRef<IHttpRequest> Request = Module->CreateRequest();

	Request->OnProcessRequestComplete().BindLambda(
		[CallBack](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
		{
			int32 ResponseCode = Response->GetResponseCode();
			switch (ResponseCode)
			{
			case 200:
				{
					FUserInfoResponse UserInfoResponse;
					GetStructFromJsonString(Response->GetContentAsString(), UserInfoResponse);
					UE_LOG(HTTPGameApiLog, Log, TEXT("User Info Response Nickname: %s, And Email: %s"), *UserInfoResponse.Nickname, *UserInfoResponse.Email);
					CallBack(true, UserInfoResponse, FErrorResponse());
				}
				break;
			case 400:
				{
					FErrorResponse ErrorResponse;
					GetStructFromJsonString(Response->GetContentAsString(), ErrorResponse);
					UE_LOG(HTTPGameApiLog, Error, TEXT("User Info Response Error: %s"), *ErrorResponse.Error);
					CallBack(true, FUserInfoResponse(), ErrorResponse); 
					break;
				}
			default:
				UE_LOG(HTTPGameApiLog, Error, TEXT("Unknown response code: %d"), ResponseCode);
				break;
			}
		});

	FString RequestString;
	if(GetJsonStringFromStruct(UserInfoRequest, RequestString))
	{
		Request->SetURL(URL);
		Request->SetVerb(TEXT("Post"));
		Request->SetHeader(TEXT("Content-Type"),TEXT("application/json"));
		Request->SetContentAsString(RequestString);
		Request->ProcessRequest();
	}
}
void UHTTPGameAPIRequestsLib::GameApiServerInfoRequest(
	TFunction<void(const bool&, const TArray<FServerInfo>&, const FErrorResponse&)> CallBack)
{
	FString URL = "http://localhost:3000/api/servers-info";
	FHttpModule* Module = &FHttpModule::Get();

	TSharedRef<IHttpRequest> Request = Module->CreateRequest();

	Request->OnProcessRequestComplete().BindLambda(
		[CallBack](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
		{
			int32 ResponseCode = Response->GetResponseCode();
			switch (ResponseCode)
			{
			case 200:
				{
					UE_LOG(HTTPGameApiLog, Warning, TEXT("ServersInfo: %s"), *Response->GetContentAsString());
					FString YourJsonString = Response->GetContentAsString();
					
					TArray<TSharedPtr<FJsonValue>> JsonValues;
					TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(YourJsonString);

					if (FJsonSerializer::Deserialize(Reader, JsonValues))
					{
						TArray<FServerInfo> ServerInfos;
						for (auto& Value : JsonValues)
						{
							TSharedPtr<FJsonObject> JsonObject = Value->AsObject();
							if (JsonObject.IsValid())
							{
								FServerInfo ServerInfo;
								FString Port = FString::FromInt(JsonObject->GetIntegerField("port"));
								int32 ConnectedPlayers = JsonObject->GetIntegerField("connectedPlayers");
								
								ServerInfo.Port = Port;
								ServerInfo.ConnectedClients = ConnectedPlayers;
								ServerInfos.Add(ServerInfo);
							}
						}
						CallBack(true, ServerInfos, FErrorResponse());
					}

				}
				break;
			default:
				CallBack(false, TArray<FServerInfo>(), FErrorResponse());
				UE_LOG(HTTPGameApiLog, Error, TEXT("Unknown response code: %d"), ResponseCode);
				break;
			}
		});


	Request->SetURL(URL);
	Request->SetVerb(TEXT("Get"));
	Request->SetHeader(TEXT("Content-Type"),TEXT("application/json"));
	Request->ProcessRequest();

}


template <typename TStruct>
bool UHTTPGameAPIRequestsLib::GetJsonStringFromStruct(TStruct FilledStruct, FString& StringOutput)
{
	return FJsonObjectConverter::UStructToJsonObjectString(TStruct::StaticStruct(), &FilledStruct, StringOutput, 0, 0);
}

template <typename TStruct>
bool UHTTPGameAPIRequestsLib::GetStructFromJsonString(const FString& JsonString, TStruct& OutputStruct)
{
	return FJsonObjectConverter::JsonObjectStringToUStruct(JsonString, &OutputStruct, 0, 0);
}
