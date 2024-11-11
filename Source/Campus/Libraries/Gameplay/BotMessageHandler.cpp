#include "BotMessageHandler.h"
TMap<int, FString> UBotMessageHandler::LocationIDToLocationInfo{
	    {1, TEXT("Кабинет русского языка")},
		{2, TEXT("Кабинет информатики")},
		{3, TEXT("Кабинет директора")},
		{4, TEXT("Кабинет математики")},
		{5, TEXT("Кабинет физики")},
		{6, TEXT("Кабинет проектных технологий")},
		{7, TEXT("Кабинет основ безопасности жизнедеятельности")},
		{8, TEXT("Кабинет экологии и биологии, истории и обществознания")},
		{9, TEXT("Кабинет химии")},
		{10, TEXT("Химическая лаборатория")},
		{11, TEXT("Кабинет астрономии")},
		{12, TEXT("Холл")}
};

TPair<int, FString> UBotMessageHandler::HandleMessage(FString Message) {
	if (Message.IsNumeric()) {
		int LocationID = FCString::Atoi(*Message);
		if (LocationIDToLocationInfo.Contains(LocationID)) {
			return TPair<int, FString>(LocationID, FString::Printf(TEXT("Мы отправляемся в %s"), *LocationIDToLocationInfo[LocationID]));
		}
	}
    
	FString LocationsList = TEXT("Приветсвтую вас в проектной школе МГТУ им. Носова, куда вы хотите отправиться:\n");
	for (const auto& Elem : LocationIDToLocationInfo) {
		LocationsList += FString::Printf(TEXT("%d. %s\n"), Elem.Key, *Elem.Value);
	}
    
	return TPair<int, FString>(0, LocationsList);
}
