#pragma once

namespace AlpinistGame
{
	class AlpinistCaretaker;
}

class UAlpinistGameHelper
{
public:
	inline static bool bInitializeViewMapProcess = false;
	static int32 DetermineNumberOfLevels(const FString& DirectoryPath)
	{
		if (FPaths::DirectoryExists(DirectoryPath))
		{
			TArray<FString> Files = TArray<FString>();
			IFileManager& FileManager = IFileManager::Get();
			FileManager.FindFiles(Files, *DirectoryPath, *FString("*.json"));

			return Files.Num();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Директория %s не существует"), *DirectoryPath);
		}
		
		return -1;
	}

	static FString GetSelectedLevelPath(const FString& DirectoryPath, int32 SelectedLevel)
	{
		FString Path = FString();

		if (FPaths::DirectoryExists(DirectoryPath))
		{
			TArray<FString> Files = TArray<FString>();
			IFileManager& FileManager = IFileManager::Get();
			FileManager.FindFiles(Files, *DirectoryPath, *FString("*.json"));

			if (SelectedLevel > 0 && SelectedLevel <= Files.Num())
			{
				return FPaths::Combine(DirectoryPath, Files[SelectedLevel - 1]);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Уровня %i не существует"), SelectedLevel);
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Директория %s не существует"), *DirectoryPath);
		}
		
		return Path;
	}

	static TArray<TPair<int32, TPair<int32, int32>>> GetAlpinistCoordinateHistory(const TWeakPtr<AlpinistGame::AlpinistCaretaker>& AlpMemento);
};