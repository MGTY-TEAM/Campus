// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Campus/MiniGames/Equilibrium/Core/EquilibriumGame.h"
#include "Components/ActorComponent.h"
#include "EquilibriumViewModelComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnChangeStates, const vector<ENodeRotationState>&);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CAMPUS_API UEquilibriumViewModelComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UEquilibriumViewModelComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void CreateModelInstance(const vector<vector<int32_t>>& Cups);
	
	FOnChangeStates OnChangeStates;
private:
	EquilibriumGame::GameEquilibrium EquilibriumModelInstance;
	
	void OnTryAddWeight(const vector<int>& Array, int Weight) const;
	void OnTryRemoveWeight(const vector<int>& Array) const;
};
