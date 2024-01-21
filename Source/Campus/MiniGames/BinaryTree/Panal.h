// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Campus/Interfaces/Interaction/Interactable.h"
#include "Campus/Interfaces/MiniGames/BinaryFruit/BinaryFruit.h"
#include "GameFramework/Actor.h"
#include "Panal.generated.h"

UCLASS()
class CAMPUS_API APanal : public AActor , public IInteractable , public IBinaryFruit
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APanal();
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* Root;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* Zero;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* One;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* Two;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* Three;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* Four;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* Five;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* Six;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* Seven;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* Eight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* DeleteButton;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* AnswerButton;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	TArray<FString> RightAnsw;
	
	int32 RightAnswers = 0;
	
	int32 AnswerNum = 0;
	
	TArray<UStaticMeshComponent*> Meshes;
	
	FTransform OldTransform;
	
	int32 k = 0;

	TArray<UPrimitiveComponent*> UsedMeshes;
	void SetupOldLocationAndAnsw();
	
public:
	
	virtual  void Interact(UActorComponent* GetComponent, const FVector& InteractPoint, const FVector& InteractionNormal) override;

	virtual void PanalI(FString a, FString b, FString c) override;
};
