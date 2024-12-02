#include "AlpinistGameHelper.h"

#include "Campus/MiniGames/Alpinist/Core/GameTypes.h"
#include "Campus/MiniGames/Alpinist/Core/AlpinistMemento.h"

TArray<TPair<int32, TPair<int32, int32>>> UAlpinistGameHelper::GetAlpinistCoordinateHistory(const TWeakPtr<AlpinistGame::AlpinistCaretaker>& AlpMemento)
{
	TArray<TPair<int32, TPair<int32, int32>>> CoordinateHistory = TArray<TPair<int32, TPair<int32, int32>>>();

	if (AlpMemento.IsValid())
	{
		for (auto& Snapshot : AlpMemento.Pin().Get()->GetPlayersHistory())
		{
			TPair<int32, TPair<int32, int32>> PlayerCoordinate = TPair<int32, TPair<int32, int32>>(static_cast<int32>(Snapshot.first), TPair<int32, int32>(Snapshot.second.first, Snapshot.second.second));
			CoordinateHistory.Add(PlayerCoordinate);
		}
	}

	return CoordinateHistory;
}

bool UAlpinistGameHelper::CheckingLevelCompletion(const FDataTableRowHandle& AlpinistDataTable, const FString& LevelName, int32 NumOfTokensForCurrentLevel)
{
	if (!AlpinistDataTable.IsNull())
	{
		if (const FAlpinistLevelRowBase* FoundAlpinistLevelRowBase = AlpinistDataTable.DataTable->FindRow<FAlpinistLevelRowBase>(FName(LevelName), TEXT("")))
		{
			if (NumOfTokensForCurrentLevel <= FoundAlpinistLevelRowBase->MaxNumCommands)
			{
				return true;
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Уровень %s не найден в Alpinist Data Table"), *LevelName);
		}
	}
		
	return false;
}
