
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Campus/Interfaces/MiniGames/MiniGames.h"
#include "Campus/Interfaces/Interaction/Interactable.h"
#include "AlpinistGame.generated.h"

class UStaticMeshComponent;
class UAlpinistIDEController;

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
public:	
	virtual void Tick(float DeltaTime) override;

	virtual void Interact(UActorComponent* InteractComponent, const FVector& InteractPoint, const FVector& InteractionNormal) override;
};
