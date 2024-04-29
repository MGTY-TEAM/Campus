// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpaceObjectSpot.generated.h"

class ASpaceObject;
class AInventoryActor;
class UStaticMeshComponent;
class UPickupSocketComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnChangeState);

UCLASS()
class CAMPUS_API ASpaceObjectSpot : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpaceObjectSpot();

	FOnChangeState OnChangeState;
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SpotSettings")
	UStaticMeshComponent* StaticHandleMeshComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SpotSettings")
	UPickupSocketComponent* PickupSocket;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpotSettings")
	FName NameOfSpot = NAME_None;
	
public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	ASpaceObject* GetCorrectPlanet() const { return CorrectPlanet; }
	
	UFUNCTION(BlueprintCallable)
	bool GetStatus() const { return HaveCorrectPlanet; }

	UFUNCTION(BlueprintCallable)
	void StopCorrectPlanet();

	UFUNCTION(BlueprintNativeEvent)
	void OnGameCompleted();

	UFUNCTION(BlueprintNativeEvent)
	void OnDestroyUniverse();
private:
	ASpaceObject* CorrectPlanet = nullptr;
	bool HaveCorrectPlanet = false;

	UFUNCTION(meta = (BlueprintProtected = "true"))
	void OnPickupPlaced(AInventoryActor* Actor);
	
	UFUNCTION(meta = (BlueprintProtected = "true"))
	void OnPickupRemoved();

	void CheckCorrectPlanet(ASpaceObject* SpaceObject);
	
	void OnGameCompleted_Implementation() {};
	void OnDestroyUniverse_Implementation() {};
};
