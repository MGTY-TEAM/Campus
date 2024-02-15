// Fill out your copyright notice in the Description page of Project Settings.


#include "BinaryTree.h"
#include "ActorReferencesUtils.h"
#include "PanalRandom.h"
#include "Runtime/Core/Tests/Containers/TestUtils.h"


// Sets default values
ABinaryTree::ABinaryTree()
{
	Tree = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tree"));
	
	Zero = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Zero"));
	One = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("One"));
	Two = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Two"));
	Three = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Three"));
	Four = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Four"));
	Five = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Five"));
	Six = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Six"));
	Seven = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Seven"));
	
	Zero->SetupAttachment(Tree);
	One->SetupAttachment(Tree);
	Two->SetupAttachment(Tree);
	Three->SetupAttachment(Tree);
	Four->SetupAttachment(Tree);
	Five->SetupAttachment(Tree);
	Six->SetupAttachment(Tree);
	Seven->SetupAttachment(Tree);

	ConstructorHelpers::FObjectFinder<UStaticMesh>Apple(TEXT("/Script/Engine.StaticMesh'/Game/Mesh/BinaryTree/YPPles/QApple.QApple'"));
	ConstructorHelpers::FObjectFinder<UStaticMesh>Banana(TEXT("/Script/Engine.StaticMesh'/Game/Mesh/BinaryTree/Banana/QBanana.QBanana'"));
	ConstructorHelpers::FObjectFinder<UStaticMesh>Blue(TEXT("/Script/Engine.StaticMesh'/Game/Mesh/BinaryTree/Blue/QBlue.QBlue'"));
	ConstructorHelpers::FObjectFinder<UStaticMesh>Cherry(TEXT("/Script/Engine.StaticMesh'/Game/Mesh/BinaryTree/Cherry/QCherry.QCherry'"));
	ConstructorHelpers::FObjectFinder<UStaticMesh>Grape(TEXT("/Script/Engine.StaticMesh'/Game/Mesh/BinaryTree/Grape/QGrape.QGrape'"));
	ConstructorHelpers::FObjectFinder<UStaticMesh>Orange(TEXT("/Script/Engine.StaticMesh'/Game/Mesh/BinaryTree/Orange/QOrange.QOrange'"));
	ConstructorHelpers::FObjectFinder<UStaticMesh>Pine(TEXT("/Script/Engine.StaticMesh'/Game/Mesh/BinaryTree/Pine/QPine.QPine'"));
	ConstructorHelpers::FObjectFinder<UStaticMesh>Straw(TEXT("/Script/Engine.StaticMesh'/Game/Mesh/BinaryTree/Straw/QStraw.QStraw'"));
	
	if (Apple.Succeeded())
	{
		MeshesObj.Add(Apple.Object);
		MeshesObj.Add(Banana.Object);
		MeshesObj.Add(Blue.Object);
		MeshesObj.Add(Cherry.Object);
		MeshesObj.Add(Grape.Object);
		MeshesObj.Add(Orange.Object);
		MeshesObj.Add(Pine.Object);
		MeshesObj.Add(Straw.Object);
	}
	
	Meshes.Add(Zero);
	Meshes.Add(One);
	Meshes.Add(Two);
	Meshes.Add(Three);
	Meshes.Add(Four);
	Meshes.Add(Five);
	Meshes.Add(Six);
	Meshes.Add(Seven);
	
	FRandomStream(time(0));
}

// Called when the game starts or when spawned
void ABinaryTree::BeginPlay()
{
	Super::BeginPlay();
}

void ABinaryTree::BinaryTreeI(int32 FirstAnswerNumber, int32 SecondAnswerNumber, int32 ThirdAnswerNumber,
                              int32 FirstMeshNumber, int32 SecondMeshNumber, int32 ThirdMeshNumber)
{
	
	Meshes[FirstAnswerNumber]->SetStaticMesh(MeshesObj[FirstMeshNumber]);
	Meshes[SecondAnswerNumber]->SetStaticMesh(MeshesObj[SecondMeshNumber]);
	Meshes[ThirdAnswerNumber]->SetStaticMesh(MeshesObj[ThirdMeshNumber]);

	 IntForRandom.Empty();
	
	 IntForRandom.Append(AllIntForRandom);
	 
	 IntForRandom.Remove(FirstMeshNumber);
	 IntForRandom.Remove(SecondMeshNumber);
	 IntForRandom.Remove(ThirdMeshNumber);

	for (int i = 0; i < IntForRandom.Num(); ++i)
	{
		IntForRandom.Swap(i,FMath::RandRange(0,IntForRandom.Num()-1));
	}

	 int32 k = 0;
	 
	 for (int i = 0; i < Meshes.Num(); i++)
	 {
	 	if (i != FirstAnswerNumber and i != SecondAnswerNumber and i != ThirdAnswerNumber)
	 	{
	 		Meshes[i]->SetStaticMesh(MeshesObj[IntForRandom[k]]);
	 		k++;
	 	}
	 }
}










