
#include "Campus/MiniGames/Alpinist/AlpinistGame.h"

#include "NiagaraComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Campus/Libraries/CampusUtils.h"
#include "Components/StaticMeshcomponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Campus/MiniGames/Alpinist/Core/GameController.h"
#include "Campus/MiniGames/Alpinist/AlpinistIDEController.h"
#include "Campus/MiniGames/Alpinist/AlpinistViewComponent.h"
#include "Campus/MiniGames/Alpinist/AlpinistAudioComponent.h"
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

	MapViewSceneComponent = CreateDefaultSubobject<USceneComponent>("MapViewSceneComponent");
	MapViewSceneComponent->SetupAttachment(GetRootComponent());

	PlayersNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>("PlayersNiagaraComponent");
	PlayersNiagaraComponent->SetupAttachment(GetRootComponent());
	WeatherNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>("WeatherNiagaraComponent");
	WeatherNiagaraComponent->SetupAttachment(GetRootComponent());

	MainMountainMeshComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>("MainMountainMeshComponent");
	MainMountainMeshComponent->SetupAttachment(GetRootComponent());
	SecondMountainMeshComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>("SecondMountainMeshComponent");
	SecondMountainMeshComponent->SetupAttachment(GetRootComponent());
	MainSnowMeshComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>("MainSnowMeshComponent");
	MainSnowMeshComponent->SetupAttachment(GetRootComponent());
	SecondSnowMeshComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>("SecondSnowMeshComponent");
	SecondSnowMeshComponent->SetupAttachment(GetRootComponent());
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	AlpinistIDEController = CreateDefaultSubobject<UAlpinistIDEController>("AlpinistIDEController");
	AlpinistViewComponent = CreateDefaultSubobject<UAlpinistViewComponent>("AlpinistViewComponent");
	AlpinistAudioComponent = CreateDefaultSubobject<UAlpinistAudioComponent>("AlpinistAudioComponent");
}

void AAlpinistGame::BeginPlay()
{
	Super::BeginPlay();

	if (PlayersNiagaraComponent)
	{
		PlayersNiagaraComponent->SetAsset(PlayersNiagaraSystem);
		PlayersNiagaraComponent->Deactivate();
	}
	if (WeatherNiagaraComponent)
	{
		WeatherNiagaraComponent->SetAsset(WeatherNiagaraSystem);
		WeatherNiagaraComponent->Deactivate();
	}
}

void AAlpinistGame::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Проверка на работу делегата при имзенении лога
	/*if (AlpinistIDEController)
	{
		AlpinistIDEController->OnAlpinistLogUpdate.Broadcast(m_AlpinistLog.Get());
	}*/
}

void AAlpinistGame::Interact(UActorComponent* InteractComponent, const FVector& InteractPoint, const FVector& InteractionNormal)
{
	if (InitializeAlpinistGame())
	{
		if (AlpinistIDEController && AlpinistIDEController->InitializeAlpinistIDE())
		{
			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			if (PlayerController && CameraComponent)
			{
				PlayerController->SetViewTargetWithBlend(this, CameraSmoothTime); // Плавный переход на статичную камеру за 1 секунду
			}
			
			// Перемещение камеры, процедурная генерация карты
			UE_LOG(LogAlpinistGame, Display, TEXT("Alpinost Game Started"));
		}
	}
}

void AAlpinistGame::SetCode(const FString& NewCode)
{
	if (m_Compiler.IsValid())
	{
		m_Compiler->SetCode(TCHAR_TO_UTF8(*NewCode));
	}
}

void AAlpinistGame::PressShoulder()
{
	if (TelegraphShoulderMeshComponent && TelegraphShoulderMeshComponent->GetRelativeRotation().Equals(FRotator(0.f, 0.f, 0.f)))
	{
		TelegraphShoulderMeshComponent->SetRelativeRotation(FRotator(5.f, 0.f, 0.f));
	}
}

void AAlpinistGame::RepressShoulder()
{
	if (TelegraphShoulderMeshComponent && TelegraphShoulderMeshComponent->GetRelativeRotation().Equals(FRotator(5.f, 0.f, 0.f)))
	{
		TelegraphShoulderMeshComponent->SetRelativeRotation(FRotator(0.f, .0f, 0.f));
	}
}

bool AAlpinistGame::InitializeAlpinistGame()
{
	if (SetupController())
	{
		if (m_gameController.IsValid())
		{
			m_Compiler = MakeShared<AlpinistGame::Compiler>(m_gameController.ToWeakPtr(), "");
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
	if (AlpinistViewComponent && JsonObject.Get() && SucceededDeserialize)
	{
		TArray<FString> Map;
		if (JsonObject->TryGetStringArrayField("game_map", Map))
		{
			AlpinistViewComponent->InitializeLevel(Map, MapViewSceneComponent, PlayersNiagaraComponent);
			AlpinistViewComponent->InitializeWeather(WeatherNiagaraComponent);
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
	if (m_Compiler.IsValid() && m_AlpinistLog.IsValid()  && AlpinistIDEController)
	{
		TWeakPtr<AlpinistGame::AlpinistLog> AlpLog = m_AlpinistLog.ToWeakPtr();
		m_Compiler->Compile(AlpLog);
		m_AlpinistLog->PushMessageLog("Build Processing Finished...", AlpinistGame::DisplayMes);
		AlpinistIDEController->OnAlpinistLogUpdate.Broadcast(m_AlpinistLog.Get());
	}
}

void AAlpinistGame::RunGame()
{
	ToStartPosition();
	if (m_Compiler.IsValid() && m_AlpinistLog.IsValid() && AlpinistIDEController && AlpinistViewComponent)
	{
		TWeakPtr<AlpinistGame::AlpinistLog> AlpLog = m_AlpinistLog.ToWeakPtr();
		m_Compiler->Run(AlpLog);
		m_AlpinistLog->PushMessageLog("Run Processing Finished...", AlpinistGame::DisplayMes);
		AlpinistViewComponent->StartPlayByHistory(UAlpinistGameHelper::GetAlpinistCoordinateHistory(m_gameController->GetAlpinistCaretaker()));
		
		if (m_gameController->GetWorld()->IsPlayerFinished())
		{
			if (!PassedLevels.Contains(SelectedLevel))
			{
				if (UAlpinistGameHelper::CheckingLevelCompletion(AlpinistDataTable, UAlpinistGameHelper::GetSelectedLevelName(UKismetSystemLibrary::GetProjectDirectory() /= "Alpinist/Levels", SelectedLevel), m_Compiler->CountTokens()))
				{
					PassedLevels.Add(SelectedLevel);
					m_AlpinistLog->PushMessageLog("Player finished, Successful completion of level " + std::to_string(SelectedLevel), AlpinistGame::SuccessMes);
				}
				else
				{
					m_AlpinistLog->PushMessageLog("Player finished, But To Pass this Level you must use fewer commands...", AlpinistGame::WarningMes);
				}
			}
			else
			{
				m_AlpinistLog->PushMessageLog("Player finished!", AlpinistGame::SuccessMes);
			}
			
			UE_LOG(LogAlpinistGame, Warning, TEXT("Player finished!"));
		}
		else
		{
			UE_LOG(LogAlpinistGame, Warning, TEXT("Player didn't finish!"));
		}
		AlpinistIDEController->OnAlpinistLogUpdate.Broadcast(m_AlpinistLog.Get());

		if (!m_AlpinistLog->bHasErrors)
		{
			if (AlpinistAudioComponent)
			{
				AlpinistAudioComponent->StartTelegraphSound(m_Compiler->GetCode());
			}
		}
	}

	if (!bAlpinistGameCompleted && PassedLevels.Num() == UAlpinistGameHelper::DetermineNumberOfLevels(UKismetSystemLibrary::GetProjectDirectory() + "Alpinist/Levels"))
	{
		ExecuteMiniGameCompleted.Broadcast();
		bAlpinistGameCompleted = true;
		UE_LOG(LogAlpinistGame, Warning, TEXT("Alpinist Game Completed!"));

		if (m_AlpinistLog.IsValid() && AlpinistIDEController)
		{
			m_AlpinistLog->PushMessageLog("Alpinist Game Completed!", AlpinistGame::SuccessMes);
			AlpinistIDEController->OnAlpinistLogUpdate.Broadcast(m_AlpinistLog.Get());
		}
	}
}

void AAlpinistGame::ClearLog()
{
	if (m_AlpinistLog.IsValid() && AlpinistIDEController)
	{
		m_AlpinistLog->ClearLog();
		AlpinistIDEController->OnAlpinistLogUpdate.Broadcast(m_AlpinistLog.Get());
	}
}

void AAlpinistGame::ToStartPosition()
{
	if (m_gameController.IsValid())
	{
		m_gameController->ToStartPositions();

		if (m_AlpinistLog.IsValid() && AlpinistIDEController)
		{
			m_AlpinistLog->PushMessageLog("ToStartPosition Processing Finished...", AlpinistGame::DisplayMes);
			AlpinistIDEController->OnAlpinistLogUpdate.Broadcast(m_AlpinistLog.Get());
		}
	}

	if (AlpinistViewComponent)
	{
		AlpinistViewComponent->ToStartPosition(PlayersNiagaraComponent);
	}
	
	if (AlpinistAudioComponent)
	{
		AlpinistAudioComponent->StopTelegraphSound();
	}
}

void AAlpinistGame::CloseGame()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController && CameraComponent)
	{
		if (PlayerController->GetPawn())
		{
			PlayerController->SetViewTargetWithBlend(PlayerController->GetPawn(), CameraSmoothTime); // Плавный переход на статичную камеру за 1 секунду
		}
	}
	if (AlpinistViewComponent)
	{
		AlpinistViewComponent->DestroyLevel(MapViewSceneComponent, PlayersNiagaraComponent);
		AlpinistViewComponent->DestroyWeather(WeatherNiagaraComponent);
	}
	if (AlpinistAudioComponent)
	{
		AlpinistAudioComponent->StopTelegraphSound();
	}
	
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
		UE_LOG(LogAlpinistGame, Display, TEXT("Path Of Selected Level: %s"), *UAlpinistGameHelper::GetSelectedLevelPath(UKismetSystemLibrary::GetProjectDirectory() /= "Alpinist/Levels", SelectedLevel));

		if (m_AlpinistLog.IsValid() && AlpinistIDEController)
		{
			m_AlpinistLog->PushMessageLog("Level Opening: " + std::string(TCHAR_TO_UTF8(*UAlpinistGameHelper::GetSelectedLevelName(UKismetSystemLibrary::GetProjectDirectory() /= "Alpinist/Levels", SelectedLevel))), AlpinistGame::DisplayMes);
			AlpinistIDEController->OnAlpinistLogUpdate.Broadcast(m_AlpinistLog.Get());
		}
	}

	// Удаление нынешней карты, генерация выбранной карты
	if (AlpinistViewComponent)
	{
		AlpinistViewComponent->DestroyLevel(MapViewSceneComponent, PlayersNiagaraComponent);
		
		const FString PathToJson = UAlpinistGameHelper::GetSelectedLevelPath(UKismetSystemLibrary::GetProjectDirectory() + "Alpinist/Levels", SelectedLevel);
		bool SucceededDeserialize = false;
		FString OutInfoMessage = FString();

		const TSharedPtr<FJsonObject> JsonObject = UHelperReaderJsonForAlpinist::ReadJson(PathToJson, SucceededDeserialize, OutInfoMessage);
		if (JsonObject.Get() && SucceededDeserialize)
		{
			TArray<FString> Map;
			if (JsonObject->TryGetStringArrayField("game_map", Map))
			{
				AlpinistViewComponent->InitializeLevel(Map, MapViewSceneComponent, PlayersNiagaraComponent);
			}
		}
	}

	if (AlpinistAudioComponent)
	{
		AlpinistAudioComponent->StopTelegraphSound();
	}
}

