// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Campus/AI/AIDrone/CoreDrone/PlayerInteractionDrone.h"
#include "Campus/Chat/MessageInstance.h"
#include "AIAnimDrone.generated.h"

class UBehaviorTree;
class UChatBox;
class UDarkeningScreen;
class ATeleportationPlane;
class UAIPerceptionStimuliSourceComponent;
class USceneComponent;
class USplineComponent;
class UChatUserComponent;


UCLASS()
class CAMPUS_API AAIAnimDrone : public APlayerInteractionDrone
{
	GENERATED_BODY()
	
public:
	AAIAnimDrone();
	
	UPROPERTY(EditAnywhere, Category = "RobotAnimation")
	float RotationSpeed = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BehaviorTreeAsset;

	UFUNCTION(BlueprintCallable)
	bool DoesHeInteract() const { return InInteraction; }

	UFUNCTION(BlueprintCallable)
	AActor* GetInteractingCharacter() const { return InteractingCharacter; }

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Rotation")
	float DroneRotationSpeed = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget")
	TSubclassOf<UUserWidget> BlueprintChatClass;
	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	UChatBox* ChatWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget")
	TSubclassOf<UUserWidget> BlueprintDarkeningClass;
	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	UDarkeningScreen* DarkWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KeyWords")
	FString BotURL;
	UPROPERTY(EditAnywhere, Category = "KeyWords")
	TArray<AActor*> TeleportationPlaces;
	UPROPERTY(EditDefaultsOnly, Category = "KeyWords")
	ATeleportationPlane* TeleportationPlace;

	virtual void StartRotateToPlayerAnim();
	virtual void StopRotateToPlayerAnim();

	UChatBox* OpenChat();
	void CloseChat();

	USceneComponent* GetSceneComponent() { return SceneComponent; }

	UFUNCTION()
	void TeleportToLocation(int index);
	UFUNCTION()
	void DarkeningScreen();
	void EndDarkeningScreen();

	FVector GetStartLocation() const { return StartLocationOfDrone; }
	USplineComponent* GetSpline() const { return SplineComponent; }
	
	bool LeadingTheCharacter = false;
protected:
	virtual void BeginPlay() override;
	
	// virtual void UnPickupOff() override;

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* SceneComponent;

	UPROPERTY(EditDefaultsOnly)
	USplineComponent* SplineComponent;

	FTimerHandle IdleAnimTimer;
	FTimerHandle RotateToPlayerTimer;
	FTimerHandle EndDarkeningTimer;

private:
	bool InInteraction = false;
	AActor* InteractingCharacter;

	FVector StartLocationOfDrone = FVector();
};
