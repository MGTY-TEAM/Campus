
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Campus/Interfaces/MiniGames/MiniGames.h"
#include "Campus/Interfaces/Interaction/Interactable.h"
#include "AlpinistGame.generated.h"

class UStaticMeshComponent;
class UAlpinistIDEController;

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
private:
	TSharedPtr<AlpinistGame::GameController> m_gameController;
	TSharedPtr<AlpinistGame::Compiler> m_Compiler;
	TSharedPtr<AlpinistGame::AlpinistLog> m_AlpinistLog;
	TSet<int32> PassedLevels;

	bool InitializeAlpinistGame();
	bool SetupController();

	bool bAlpinistGameCompleted = false;
};