// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Campus/Interfaces/Interaction/Interactable.h"
#include "Campus/Interfaces/MiniGames/BinaryFruit/BinaryFruit.h"
#include "GameFramework/Actor.h"
#include "Panall.generated.h"

UCLASS()
class CAMPUS_API APanall : public AActor , public IInteractable , public IBinaryFruit
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APanall();
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Root;
	
	UPROPERTY(EditAnywhere);
	UStaticMeshComponent* Zero;

	UPROPERTY(EditAnywhere);
	UStaticMeshComponent* One;

	UPROPERTY(EditAnywhere);
	UStaticMeshComponent* Two;

	UPROPERTY(EditAnywhere);
	UStaticMeshComponent* Three;

	UPROPERTY(EditAnywhere);
	UStaticMeshComponent* Four;
	
	UPROPERTY(EditAnywhere);
	UStaticMeshComponent* Five;

	UPROPERTY(EditAnywhere);
	UStaticMeshComponent* Six;

	UPROPERTY(EditAnywhere);
	UStaticMeshComponent* Seven;

	UPROPERTY(EditAnywhere);
	UStaticMeshComponent* Eight;

//	UPROPERTY(BlueprintReadWrite , EditAnywhere)
//	TArray<FString> RightA;
	
	int16 RAnswers = 0;
	int16 AnswerN = 0;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual  void Interact(UPrimitiveComponent* GetComponent, ABaseFirstPersonCharacter* SelfCharacter) override;
	

};
