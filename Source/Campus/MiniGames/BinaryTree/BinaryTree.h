// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorReferencesUtils.h"
#include "Campus/Interfaces/Interaction/Interactable.h"
#include "Campus/Interfaces/MiniGames/BinaryFruit/BinaryFruit.h"
#include "GameFramework/Actor.h"
#include "UObject/UObjectGlobals.h"
#include "BinaryTree.generated.h"

UCLASS()
class CAMPUS_API ABinaryTree : public AActor , public IBinaryFruit
{
	GENERATED_BODY()

protected:
	// Sets default values for this actor's properties
	ABinaryTree();

	UPROPERTY(EditAnywhere);
	UStaticMeshComponent* Tree;

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
	

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TArray<int32> AllIntForRandom {0,1,2,3,4,5,6,7};
	TArray<int32> IntForRandom;


	TArray<UStaticMesh*> MeshesObj;
	TArray<UStaticMeshComponent*> Meshes;

public:
	
	virtual void BinaryTreeI(int32 FirstAnswerNumber, int32 SecondAnswerNumber, int32 ThirdAnswerNumber, int32 FirstMeshNumber, int32 SecondMeshNumber, int32 ThirdMeshNumber) override;

};
