// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Campus/AI/AIDrone/CoreDrone/PlayerInteractionDrone.h"
#include "AIAnimDrone.generated.h"

class UBehaviorTree;
class UChatBox;
class UDarkeningScreen;
class ATeleportationPlane;

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

	UFUNCTION()
	void TeleportToLocation(int index);
	UFUNCTION()
	void DarkeningScreen();
	void EndDarkeningScreen();
protected:
	virtual void BeginPlay() override;

	virtual void UnPickupOn(AActor* Character) override;
	virtual void UnPickupOff() override;

	FTimerHandle IdleAnimTimer;
	FTimerHandle RotateToPlayerTimer;
	FTimerHandle EndDarkeningTimer;

private:
	bool InInteraction = false;
	AActor* InteractingCharacter;
};
