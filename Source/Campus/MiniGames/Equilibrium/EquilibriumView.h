// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Campus/MiniGames/Equilibrium/Core/EquilibriumTypes.h"
#include "GameFramework/Actor.h"
#include "EquilibriumView.generated.h"

class UEquilibriumViewModelComponent;
class AAEquilElement;
class AEquilNode;
class AEquilCup;

UCLASS()
class CAMPUS_API AEquilibriumView : public AActor
{
	GENERATED_BODY()
	
public:	
	AEquilibriumView();

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, Category = "Equilibrium")
	USceneComponent* SceneComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equilibrium")
	TSubclassOf<AEquilNode> SpawnableNodeClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equilibrium")
	TSubclassOf<AEquilCup> SpawnableCupClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Equilibrium")
	UEquilibriumViewModelComponent* EquilibriumViewModelComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Equilibrium")
	TObjectPtr<class UStaticMesh> StaticMeshForRootNode;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Equilibrium")
	TObjectPtr<class UStaticMesh> StaticMeshForRootArm;
public:	
	TArray<AEquilCup*> GetAllCups() const { return Cups; }

	void CreateEquilibrium(const TArray<FString>& CupsCoor);
private:
	void AddCupToArrayOfCups(AEquilCup* NewCup);

	UPROPERTY()
	AAEquilElement* Root;

	/**
	 * Coordinates of Cups.
	 */
	UPROPERTY()
	TArray<FString> CupsCoo{};

	/**
	 * Pointers to all cups.
	 */
	UPROPERTY()
	TArray<AEquilCup*> Cups{};

	void SetCoordinatesForCups();
	void SetNewStates(AEquilNode* RootNode, std::vector<EquilibriumTypes::ENodeRotationState>& RotationStates);
	void CalculateRotation(const std::vector<EquilibriumTypes::ENodeRotationState>& RotationStates);
	void CalculateRotation(AAEquilElement* RootElem);
	
	UChildActorComponent* CreateNode(AEquilNode* Current, const AAEquilElement* Child, USceneComponent* Position);
	UChildActorComponent* CreateCup(USceneComponent* Position, const FString& CupCoo);
};
