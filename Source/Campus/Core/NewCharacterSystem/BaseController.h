// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Campus/Chat/ChatUserComponent.h"
#include "GameFramework/PlayerController.h"
#include "BaseController.generated.h"

class ABaseHUD;
class UInteractionComponent;
/**
 * 
 */
UCLASS()
class CAMPUS_API ABaseController : public APlayerController
{
	GENERATED_BODY()

	ABaseHUD* BaseHUD;
		
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UChatUserComponent* ChatUserComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Classes")
	TSubclassOf<ABaseHUD> BaseHudClass;
public :

	ABaseController();
protected:
	UFUNCTION()
	void ReceiveMessage(UMessageInstance* MessageInstance);
	virtual void BeginPlay() override;
	virtual void SpawnDefaultHUD() override;

	void OnChatButtonClicked();
	void OnEscapeMenuButtonClicked();
	virtual void SetupInputComponent() override;
};
