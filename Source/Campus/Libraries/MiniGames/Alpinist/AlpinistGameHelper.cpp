#include "AlpinistGameHelper.h"

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
