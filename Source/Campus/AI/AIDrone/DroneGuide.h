// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../Drone/TeleportationPlane.h"
#include "CoreDrone/DefaultAnimDrone.h"
#include "../../UserInterface/DarkeningScreen.h"
#include "DroneGuide.generated.h"

/**
 * 
 */
class ABaseFirstPersonCharacter;
class UChatBox;

UENUM(BlueprintType)
enum class EDroneGuide : uint8
{
	Drone_Idle UMETA(DisplayName = "Idle"),
	Drone_PlayerInteract UMETA(DisplayName = "PlayerInteract"),
	Drone_Talk UMETA(DisplayName = "Talk"),
	Drone_Loading UMETA(DisplayName = "Loading")
};

UCLASS()
class CAMPUS_API ADroneGuide : public ADefaultAnimDrone
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget")
	TSubclassOf<UUserWidget> BlueprintChatClass;
	UPROPERTY(EditDefaultsOnly,Category="Widget")
	UChatBox* ChatWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget")
	TSubclassOf<UUserWidget> BlueprintDarkeningClass;
	UPROPERTY(EditDefaultsOnly,Category="Widget")
	UDarkeningScreen* DarkWidget;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="KeyWords")
	FString BotURL;
	UPROPERTY(EditAnywhere, Category="KeyWords")
	TArray<AActor*> TeleportationPlaces;
	UPROPERTY(EditDefaultsOnly, Category="KeyWords")
	ATeleportationPlane* TeleportationPlace;

	UPROPERTY(EditDefaultsOnly, Category="CharacterAnimation")
	float CharacterRotationSpeed = 2.f;
	UPROPERTY(EditDefaultsOnly, Category="CharacterAnimation")
	float CharacterStepSpeed = 0.5f;

	AActor* InteractCharacter;

	FTimerHandle EndDarkeningTimer;
	

	UFUNCTION()
	void TeleportToLocation(int index);
	UFUNCTION()
	void DarkeningScreen();
	void EndDarkeningScreen();

protected:

	virtual void BeginPlay() override;
	
	virtual void UnPickupOn(AActor* Character) override;
	virtual void UnPickupOff() override;
	void ChangeState(EDroneGuide State, float Duration = 0);

	void StartRotateCharacter(ACharacter* InteractedCharacter);

	virtual void StartIdleAnim() override;
	virtual void StopIdleAnim() override;
	virtual void StartRotateToPlayerAnim() override;
	virtual void StopRotateToPlayerAnim() override;

	void OpenChat();
	void CloseChat();

	
};
