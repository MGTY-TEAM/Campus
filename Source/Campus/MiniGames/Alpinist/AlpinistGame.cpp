
#include "Campus/MiniGames/Alpinist/AlpinistGame.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Campus/Libraries/CampusUtils.h"
#include "Components/StaticMeshcomponent.h"
#include "Campus/MiniGames/Alpinist/Core/GameController.h"
#include "Campus/MiniGames/Alpinist/AlpinistIDEController.h"
#include "Campus/Tests/Alpinist/UHelperReaderJsonForAlpinist.h"
#include "Campus/Libraries/MiniGames/Alpinist/AlpinistGameHelper.h"
#include "Campus/MiniGames/Alpinist/Core/AlpinistLanguage/Compiler.h"

DEFINE_LOG_CATEGORY_STATIC(LogAlpinistGame, All, All);

AAlpinistGame::AAlpinistGame()
{
	PrimaryActorTick.bCanEverTick = true;

	TelegraphBaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("TelegraphBaseMeshComponent");
	SetRootComponent(TelegraphBaseMeshComponent);

	TelegraphShoulderMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("TelegraphShoulderMeshComponent");
	TelegraphShoulderMeshComponent->SetupAttachment(TelegraphBaseMeshComponent);

	AlpinistIDEController = CreateDefaultSubobject<UAlpinistIDEController>("AlpinistIDEController");
}

void AAlpinistGame::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAlpinistGame::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAlpinistGame::Interact(UActorComponent* InteractComponent, const FVector& InteractPoint, const FVector& InteractionNormal)
{
	if (InitializeAlpinistGame())
	{
		if (AlpinistIDEController && AlpinistIDEController->InitializeAlpinistIDE())
		{
			// Перемещение камеры, процедурная генерация карты
			UE_LOG(LogAlpinistGame, Display, TEXT("Alpinost Game Started"));
		}
	}
}

bool AAlpinistGame::InitializeAlpinistGame()
{
	if (SetupController())
	{
		if (m_gameController.IsValid())
		{
			m_Compiler = MakeShared<AlpinistGame::Compiler>(m_gameController.Get(), "");
			m_AlpinistLog = MakeShared<AlpinistGame::AlpinistLog>();
				
			if (m_Compiler.IsValid() && m_AlpinistLog.IsValid())
			{
				return true;
			}
		}
	}
	return false;
}

bool AAlpinistGame::SetupController()
{
	const FString PathToJson = UAlpinistGameHelper::GetSelectedLevelPath(UKismetSystemLibrary::GetProjectDirectory() + "Alpinist/Levels", SelectedLevel);
	bool SucceededDeserialize = false;
	FString OutInfoMessage = FString();

	const TSharedPtr<FJsonObject> JsonObject = UHelperReaderJsonForAlpinist::ReadJson(PathToJson, SucceededDeserialize, OutInfoMessage);
	if (JsonObject.Get() && SucceededDeserialize)
	{
		TArray<FString> Map;
		if (JsonObject->TryGetStringArrayField("game_map", Map))
		{
			const std::vector<std::string> STDMap = CampusUtils::TArrayOfStringToVectorOfString(Map);
			if (m_gameController.IsValid())
			{
				m_gameController->SetNewMap(STDMap);
				return true;
			}
			m_gameController = MakeShared<AlpinistGame::GameController>(STDMap);
			return true;
		}
	}
	else
	{
		UE_LOG(LogAlpinistGame, Warning, TEXT("%s"), *OutInfoMessage);
	}
	return false;
}

void AAlpinistGame::BuildGame()
{
	if (m_Compiler.IsValid() && AlpinistIDEController)
	{
		m_Compiler->Compile(*m_AlpinistLog);
		AlpinistIDEController->OnAlpinistLogUpdate.Broadcast(m_AlpinistLog.Get());
	}
}

void AAlpinistGame::RunGame()
{
	if (m_Compiler.IsValid() && AlpinistIDEController)
	{
		m_Compiler->Run(*m_AlpinistLog);
		AlpinistIDEController->OnAlpinistLogUpdate.Broadcast(m_AlpinistLog.Get());
	}
	// Получить сформированные команды для работы с видом или написать код для связи с видом внутри написанного кода игры
}

void AAlpinistGame::ToStartPosition()
{
	// Как возвращать пешку обратно?
}

void AAlpinistGame::CloseGame()
{
	// Возвращение камеры персонажу, удаление карты
	
	if (m_Compiler.IsValid())
	{
		m_Compiler.Reset();
	}
	if (m_gameController.IsValid())
	{
		m_gameController.Reset();
	}
	if (m_AlpinistLog.IsValid())
	{
		m_AlpinistLog.Reset();
	}
}

void AAlpinistGame::OpenLevel(int32 Level)
{
	if (Level == SelectedLevel) return;
	
	if (m_gameController.IsValid())
	{
		SelectedLevel = Level;
		SetupController();
		UE_LOG(LogAlpinistGame, Display, TEXT("Path Of Selected Level: %s"), *UAlpinistGameHelper::GetSelectedLevelPath(UKismetSystemLibrary::GetProjectDirectory() + "Alpinist/Levels", SelectedLevel));
	}

	// Удалание нынешней карты, процедурная генерация выбранной карты
}

