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

	virtual void OnConstruction(const FTransform& Transform) override;
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
public:	
	virtual void Tick(float DeltaTime) override;
	
	TArray<AEquilCup*> GetAllCups() const { return Cups; }

	void CreateEquilibrium(const TArray<FString>& CupsCoor);
private:
	void AddCupToArrayOfCups(AEquilCup* NewCup);

	UPROPERTY()
	AAEquilElement* Root;
	
	UPROPERTY()
	TArray<FString> CupsCoo{};

	UPROPERTY()
	TArray<AEquilCup*> Cups{};

	std::vector<int32_t> FStringToVectorOfInt(const FString& StringToInt) const;
	std::vector<std::vector<int32_t>> TArrayOfFStringToVectorOfVectorOfInt(const TArray<FString>& TArrayToConv) const;

	void SetCoordinatesForCups();
	void SetNewStates(AEquilNode* RootNode, std::vector<EquilibriumTypes::ENodeRotationState>& RotationStates);
	void CalculateRotation(const std::vector<EquilibriumTypes::ENodeRotationState>& RotationStates);
	void CalculateRotation(AAEquilElement* RootElem);
};
