// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Campus/Chat/Components/ChatUserComponent.h"
#include "AIDroneController.generated.h"

class UAIDronePerceptionComponent;

UCLASS()
class CAMPUS_API AAIDroneController : public AAIController
{
	GENERATED_BODY()
	
public:
	AAIDroneController();

	UChatUserComponent* GetChatComponent();
protected:
	virtual void OnPossess(APawn* InPawn) override;

	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UAIDronePerceptionComponent* AIDronePerceptionComponent;
	
	UChatUserComponent* ChatUserComponent;
};
