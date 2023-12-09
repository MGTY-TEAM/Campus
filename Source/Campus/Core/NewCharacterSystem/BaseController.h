// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BaseController.generated.h"

class UInteractionComponent;
/**
 * 
 */
UCLASS()
class CAMPUS_API ABaseController : public APlayerController
{
	GENERATED_BODY()


	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UChatUserComponent* ChatUserComponent;
	
public:

	ABaseController();
protected:
	virtual void BeginPlay() override;

	void OnChatButtonClicked();
	void OnEscapeMenuButtonClicked();
	virtual void SetupInputComponent() override;
};
