// Fill out your copyright notice in the Description page of Project Settings.


#include "BinaryTree.h"
#include "ActorReferencesUtils.h"
#include "PanalRandom.h"


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

	ConstructorHelpers::FObjectFinder<UStaticMesh> Apple(TEXT("/Script/Engine.StaticMesh'/Game/Mesh/BinaryTree/YPPles/QApple.QApple'"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> Banana(TEXT("/Script/Engine.StaticMesh'/Game/Mesh/BinaryTree/Banana/QBanana.QBanana'"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> Blue(TEXT("/Script/Engine.StaticMesh'/Game/Mesh/BinaryTree/Blue/QBlue.QBlue'"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> Cherry(TEXT("/Script/Engine.StaticMesh'/Game/Mesh/BinaryTree/Cherry/QCherry.QCherry'"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> Grape(TEXT("/Script/Engine.StaticMesh'/Game/Mesh/BinaryTree/Grape/QGrape.QGrape'"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> Orange(TEXT("/Script/Engine.StaticMesh'/Game/Mesh/BinaryTree/Orange/QOrange.QOrange'"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> Pine(TEXT("/Script/Engine.StaticMesh'/Game/Mesh/BinaryTree/Pine/QPine.QPine'"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> Straw(TEXT("/Script/Engine.StaticMesh'/Game/Mesh/BinaryTree/Straw/QStraw.QStraw'"));
	
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

void ABinaryTree::BinaryTreeI(int32 a, int32 b, int32 c, FString F, FString S, FString T)
{
	Meshes[a]->SetStaticMesh(MeshesObj[AllAnswString.Find(F)]);
	Meshes[b]->SetStaticMesh(MeshesObj[AllAnswString.Find(S)]);
	Meshes[c]->SetStaticMesh(MeshesObj[AllAnswString.Find(T)]);

	IntForRandom.Empty();
	
	// Set Int array by AllInt
	for (int i = 0; i < AllIntForRandom.Num() ; ++i)
	{
		IntForRandom.Add(AllIntForRandom[i]);
	}
	// Remove using item
	IntForRandom.Remove(AllAnswString.Find(F));
	IntForRandom.Remove(AllAnswString.Find(S));
	IntForRandom.Remove(AllAnswString.Find(T));
	// Random int array
	for (int i = 0; i < IntForRandom.Num(); ++i)
	{
		IntForRandom.Swap(i,FMath::RandRange(0,IntForRandom.Num()-1));
	}

	int k = 0;
	// Set static Meshes by array Int 	
	for (int i = 0; i < Meshes.Num() ; ++i)
	{
		if (i!=a and  i!=b and i!=c)
		{

			Meshes[i]->SetStaticMesh(MeshesObj[IntForRandom[k]]);
			k++;
		}
	}
}











