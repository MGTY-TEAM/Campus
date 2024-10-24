
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Campus/Interfaces/MiniGames/MiniGames.h"
#include "Campus/Interfaces/Interaction/Interactable.h"
#include "AlpinistGame.generated.h"

class UNiagaraSystem;
class USceneComponent;
class UCameraComponent;
class UNiagaraComponent;
class UStaticMeshComponent;
class UAlpinistIDEController;
class UAlpinistViewComponent;

namespace AlpinistGame
{
	class Compiler;
	class AlpinistLog;
	class GameController;
}

UCLASS()
class CAMPUS_API AAlpinistGame : public AActor, public IMiniGames, public IInteractable
{
	GENERATED_BODY()
	
public:	
	AAlpinistGame();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* TelegraphBaseMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* TelegraphShoulderMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UAlpinistIDEController* AlpinistIDEController;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UAlpinistViewComponent* AlpinistViewComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	USceneComponent* MapViewSceneComponent;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "NiagaraPlayersSettings")
	UNiagaraSystem* PlayersNiagaraSystem;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UNiagaraComponent* PlayersNiagaraComponent;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "NiagaraPlayersSettings")
	UNiagaraSystem* WeatherNiagaraSystem;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UNiagaraComponent* WeatherNiagaraComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "EntityComponents")
	UInstancedStaticMeshComponent* MainMountainMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "EntityComponents")
	UInstancedStaticMeshComponent* SecondMountainMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "EntityComponents")
	UInstancedStaticMeshComponent* MainSnowMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "EntityComponents")
	UInstancedStaticMeshComponent* SecondSnowMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (ClampMin = "0.1", ClampMax = "5"))
	float CameraSmoothTime = 1.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AlpinistsProperties")
	int32 SelectedLevel = 1;
public:	
	virtual void Tick(float DeltaTime) override;

	virtual void Interact(UActorComponent* InteractComponent, const FVector& InteractPoint, const FVector& InteractionNormal) override;
	void SetCode(const FString& NewCode);
	void BuildGame();
	void RunGame();
	void ClearLog();
	void ToStartPosition();
	void CloseGame();
	void OpenLevel(int32 Level);

	int32 GetSelectedLevel() const { return SelectedLevel; }
	TSet<int32> GetPassedLevels() const { return PassedLevels; }

	UInstancedStaticMeshComponent* GetMainMountainMeshComponent() const { return MainMountainMeshComponent; }
	UInstancedStaticMeshComponent* GetSecondMountainMeshComponent() const { return SecondMountainMeshComponent; }
	UInstancedStaticMeshComponent* GetMainSnowMeshComponent() const { return MainSnowMeshComponent; }
	UInstancedStaticMeshComponent* GetSecondSnowMeshComponent() const { return SecondSnowMeshComponent; }
private:
	TSharedPtr<AlpinistGame::GameController> m_gameController;
	TSharedPtr<AlpinistGame::Compiler> m_Compiler;
	TSharedPtr<AlpinistGame::AlpinistLog> m_AlpinistLog;
	TSet<int32> PassedLevels;

	bool InitializeAlpinistGame();
	bool SetupController();

	bool bAlpinistGameCompleted = false;
};
