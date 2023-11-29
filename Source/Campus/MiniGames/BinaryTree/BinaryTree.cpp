// Fill out your copyright notice in the Description page of Project Settings.


#include "BinaryTree.h"
#include "ActorReferencesUtils.h"
#include "PanalRandom.h"


// Sets default values
ABinaryTree::ABinaryTree()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

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

	ConstructorHelpers::FObjectFinder<UStaticMesh>Apple(TEXT("/Script/Engine.StaticMesh'/Game/Mesh/BinaryTree/Apple/QApple.QApple'"));
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
	// Array.Add(MeshAsset);
	//
	// Zero->SetStaticMesh(Array[0].Object);
	
}

// Called when the game starts or when spawned
void ABinaryTree::BeginPlay()
{
	Super::BeginPlay();
	// APanalRandom* PanelR = NewObject<APanalRandom>(GetWorld(), TEXT("GRE"));
	// GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::SanitizeFloat(PanelR->FirstAnsw));
	// PanelR->GetFirst();

	
}



int64 ABinaryTree::ToBinary(int32 num)
{
	int bin = 0, k = 1;

	while (num)
	{
		bin += (num % 2) * k;
		k *= 10;
		num /= 2;
	}

	return bin;
}

void ABinaryTree::Work()
{
	Meshes[1]->SetStaticMesh(MeshesObj[0]);
}

void ABinaryTree::BinaryTreeI(int32 a, int32 b, int32 c, FString F, FString S, FString T)
{
	Meshes[a]->SetStaticMesh(MeshesObj[AllAnswString.Find(F)]);
	Meshes[b]->SetStaticMesh(MeshesObj[AllAnswString.Find(S)]);
	Meshes[c]->SetStaticMesh(MeshesObj[AllAnswString.Find(T)]);
	
	// Set int array by AllInt
	for (int i = 0; i < AllInt.Num() ; ++i)
	{
		Int.Add(AllInt[i]);
	}
	// Remove using item
	Int.Remove(AllAnswString.Find(F));
	Int.Remove(AllAnswString.Find(S));
	Int.Remove(AllAnswString.Find(T));
	// Random int array
	for (int i = 0; i < Int.Num(); ++i)
	{
		Int.Swap(i,FMath::RandRange(0,Int.Num()-1));
	}

	int k = 0;
	
	for (int i = 0; i < Meshes.Num() ; ++i)
	{
		if (i!=a and  i!=b and i!=c)
		{

			Meshes[i]->SetStaticMesh(MeshesObj[Int[k]]);
			k++;
		}
	}
}

// void ABinaryTree::BinaryTreeI(int32 a, int32 b, int32 c,  FString F, FString S, FString T)
// {
// 	
// 	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, Meshes[1]->GetName());
//
// 	Work();
// 	Meshes[b]->SetStaticMesh(MeshesObj[AllAnswString.Find(F)]);
// 	Meshes[c]->SetStaticMesh(MeshesObj[AllAnswString.Find(F)]);
// }










