// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Campus/Interfaces/Interaction/Interactable.h"
#include "GameFramework/Actor.h"
#include "InventoryActor.generated.h"

class USpringArmComponent;

UCLASS()
class CAMPUS_API AInventoryActor : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	AInventoryActor();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* SceneComponent;	
	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly, Category="Scene Capture")
	USpringArmComponent* SpringArmComponent;
	
	UPROPERTY(EditDefaultsOnly, Category = "Scene Capture")
	USceneCaptureComponent2D* SceneCaptureComponent;
	
public:
	virtual void Tick(float DeltaTime) override;
	
	UTexture2D* GetRenderTargetTexture() const;

	//POOL FUNCTIONS
	void SetEnabled(bool bEnabled);
	//
private:
	UTextureRenderTarget2D* RenderTarget;
};
