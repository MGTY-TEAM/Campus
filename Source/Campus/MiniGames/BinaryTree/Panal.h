// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Campus/Interfaces/Interaction/Interactable.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Panal.generated.h"

UCLASS()
class CAMPUS_API APanal : public AActor , public IInteractable ,public IBinaryFruit
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
	TArray<FString> RightA;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 RAnswers = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 AnswerN = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<UStaticMeshComponent*> Meshes;

	FTransform OldTransform;

	int32 k = 0;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	
	virtual  void Interact(UPrimitiveComponent* GetComponent, ABaseFirstPersonCharacter* SelfCharacter) override;

	virtual void PanalI(FString a, FString b, FString c) override;;
};
