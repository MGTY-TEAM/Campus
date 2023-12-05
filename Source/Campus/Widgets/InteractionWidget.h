// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractionWidget.generated.h"

struct FAIRequestID;
struct FPathFollowingResult;
class AAIDroneController;

UCLASS()
class CAMPUS_API UInteractionWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	bool CanHelp();

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool NeedHelpAfterArrived();

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool CanInteract();

protected:
	virtual void NativeOnInitialized() override;

private:
	bool HeHasArrived = false;
	bool bCanInteract = false;
};
