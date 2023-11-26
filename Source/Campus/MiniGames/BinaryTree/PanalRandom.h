// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Campus/Interfaces/Interaction/Interactable.h"
#include "Campus/Interfaces/MiniGames/BinaryFruit/BinaryFruit.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"  
#include "Kismet/GameplayStatics.h"
#include "PanalRandom.generated.h"

UCLASS()
class CAMPUS_API APanalRandom : public AActor , public IInteractable , public IBinaryFruit
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Mesh")
	UTextRenderComponent* TextRender;
	
	UPROPERTY(EditAnywhere, Category = "Mesh")
	UBoxComponent* CollisionMesh;
	

public:
	// Sets default values for this actor's properties
	APanalRandom();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame

	virtual void Interact(AActor* InteractedActor, AActor* SelfCharacter) override;
	
	int32 GenerateNum();


	TArray<FString> AllAnswString {"apple","banana","blue","cherry","grape","orange","pine","straw"}; 
	
	int32 FirstAnsw = 0;
	int32 SecondAnsw = 0;
	int32 ThirdAnsw = 0;

	FString FirstAnswString = "";
	FString SecondAnswString = "";
	FString ThirdAnswString = "";
	

	FString ToBinary(int32 num);

	
};
