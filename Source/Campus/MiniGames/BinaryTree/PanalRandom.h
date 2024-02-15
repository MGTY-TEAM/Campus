// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items.h"
#include "Campus/Interfaces/Interaction/Interactable.h"
#include "Campus/Interfaces/MiniGames/BinaryFruit/BinaryFruit.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"  
#include "PanalRandom.generated.h"

UCLASS()
class CAMPUS_API APanalRandom : public AActor , public IInteractable , public IBinaryFruit , public Items
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(EditAnywhere, Category = "Mesh")
	UTextRenderComponent* TextRender;
	
	UPROPERTY(EditAnywhere, Category = "Mesh")
	UBoxComponent* CollisionMesh;
	
	// Sets default values for this actor's properties
	APanalRandom();


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	//Using only for debug
	TArray<FString> AllAnswString {"apple","banana","blue","cherry","grape","orange","pine","straw"}; 
	
	int32 FirstAnsw = 0;
	int32 SecondAnsw = 0;
	int32 ThirdAnsw = 0;
	
	int32 FirstAnswMesh = 0;
	int32 SecondAnswMesh = 0;
	int32 ThirdAnswMesh = 0;
	
	FString ToBinary(int32 num);

public:
	UPROPERTY(BlueprintAssignable , BlueprintCallable , BlueprintReadWrite)
	FRandom RandomWork;
	virtual void Interact(UActorComponent* InteractComponent, const FVector& InteractPoint, const FVector& InteractionNormal) override;

};
