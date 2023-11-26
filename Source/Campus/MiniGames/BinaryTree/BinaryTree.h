// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorReferencesUtils.h"
#include "PanalRandom.h"
#include "Panal.h"
#include "Campus/Interfaces/Interaction/Interactable.h"
#include "Campus/Interfaces/MiniGames/BinaryFruit/BinaryFruit.h"
#include "GameFramework/Actor.h"
#include "UObject/UObjectGlobals.h"
#include "BinaryTree.generated.h"

UCLASS()
class CAMPUS_API ABinaryTree : public AActor  , public IInteractable , public IBinaryFruit
{
	GENERATED_BODY()

public:
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



	TArray<int32> RightAnswers;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

public:

	TArray<ConstructorHelpers::FObjectFinder<UStaticMesh>> Array;
	
	int64 ToBinary(int32 num);

	TArray<FString> RightAnswString;

	TArray<FString> AllAnswString {"apple","banana","blue","cherry","grape","orange","pine","straw"};
	TArray<FString> AnswString ;
	TArray<UStaticMesh*> MeshesObj ;
	TArray<UStaticMeshComponent*> Meshes ;

	void Work();
	
	virtual void BinaryTreeI(int32 a, int32 b, int32 c, FString F, FString S, FString T) override;

};
