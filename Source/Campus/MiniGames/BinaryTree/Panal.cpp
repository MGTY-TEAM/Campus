// Fill out your copyright notice in the Description page of Project Settings.


#include "Panal.h"


// Sets default values
APanal::APanal()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root"));
	Zero = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Zero"));
	One = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("One"));
	Two = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Two"));
	Three = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Three"));
	Four = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Four"));
	Five = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Five"));
	Six = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Six"));
	Seven = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Seven"));
	Eight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Eight"));



	RootComponent = Root;

	Zero->SetupAttachment(Root);
	One->SetupAttachment(Root);
	Two->SetupAttachment(Root);
	Three->SetupAttachment(Root);
	Four->SetupAttachment(Root);
	Five->SetupAttachment(Root);
	Six->SetupAttachment(Root);
	Seven->SetupAttachment(Root);
	Eight->SetupAttachment(Root);
	// Zero->Rename(TEXT("apple"));
	//
	//
	ConstructorHelpers::FObjectFinder<UStaticMesh>Zer(TEXT("/Script/Engine.StaticMesh'/Game/Mesh/BinaryTree/ControlPanal/domofon__1__B1.domofon__1__B1'"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh123(TEXT("/Script/Engine.StaticMesh'/Game/Mesh/BinaryTree/ControlPanal/domofon__1__Body.domofon__1__Body'"));
	
	if (Zer.Succeeded())
	{
		Root->SetStaticMesh(Mesh123.Object);
		Zero->SetStaticMesh(Zer.Object);
	}

	//

	//
	// Zero->SetRelativeLocation(FVector(0,200,650));
	//
	Zero->SetNotifyRigidBodyCollision(true);
	Zero->SetCollisionProfileName(TEXT("BlockAll"));
	One->SetNotifyRigidBodyCollision(true);
	One->SetCollisionProfileName(TEXT("BlockAll"));
	Two->SetNotifyRigidBodyCollision(true);
	Two->SetCollisionProfileName(TEXT("BlockAll"));
	Three->SetNotifyRigidBodyCollision(true);
	Three->SetCollisionProfileName(TEXT("BlockAll"));
	Four->SetNotifyRigidBodyCollision(true);
	Four->SetCollisionProfileName(TEXT("BlockAll"));
	Five->SetNotifyRigidBodyCollision(true);
	Five->SetCollisionProfileName(TEXT("BlockAll"));
	Six->SetNotifyRigidBodyCollision(true);
	Six->SetCollisionProfileName(TEXT("BlockAll"));
	Seven->SetNotifyRigidBodyCollision(true);
	Seven->SetCollisionProfileName(TEXT("BlockAll"));
	Eight->SetNotifyRigidBodyCollision(true);
	Eight->SetCollisionProfileName(TEXT("BlockAll"));

	Meshes.Add(Zero);
	Meshes.Add(One);
	Meshes.Add(Two);
	Meshes.Add(Three);
	Meshes.Add(Four);
	Meshes.Add(Five);
	Meshes.Add(Six);
	Meshes.Add(Seven);
	Meshes.Add(Eight);
}

// Called when the game starts or when spawned
void APanal::BeginPlay()
{
	Super::BeginPlay();
}



void APanal::Interact(UPrimitiveComponent* GetComponent, ABaseFirstPersonCharacter* SelfCharacter)
{
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, RightA[0]);
	if (GetComponent == Zero)
	{
		if (RightA[AnswerN] == GetComponent->GetMaterial(0)->GetName())
		 {
			RAnswers-=-1;
			GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, GetComponent->GetMaterial(0)->GetName());
		 }
	}
	if (GetComponent == One)
	{
		if (AnswerN < RightA.Num() and RightA[AnswerN] == GetComponent->GetMaterial(0)->GetName())
		{
			RAnswers-=-1;
			GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, GetComponent->GetMaterial(0)->GetName());
		}
	}
	if (GetComponent == Two)
	{
		if (AnswerN < RightA.Num() and RightA[AnswerN] == GetComponent->GetMaterial(0)->GetName())
		{
			RAnswers-=-1;
			GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, GetComponent->GetMaterial(0)->GetName());
		}
	}
	if (GetComponent == Three)
	{
		if (AnswerN < RightA.Num() and RightA[AnswerN] == GetComponent->GetMaterial(0)->GetName())
		{
			RAnswers-=-1;
			GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, GetComponent->GetMaterial(0)->GetName());
		}
	}
	if (GetComponent == Four)
	{
		if (AnswerN < RightA.Num() and RightA[AnswerN] == GetComponent->GetMaterial(0)->GetName())
		{
			RAnswers-=-1;
			GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, GetComponent->GetMaterial(0)->GetName());
		}
	}
	if (GetComponent == Five)
	{
		if (AnswerN < RightA.Num() and RightA[AnswerN] == GetComponent->GetMaterial(0)->GetName())
		{
			RAnswers-=-1;
			GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, GetComponent->GetMaterial(0)->GetName());
		}
	}
	if (GetComponent == Six)
	{
		if (AnswerN < RightA.Num() and RightA[AnswerN] == GetComponent->GetMaterial(0)->GetName())
		{
			RAnswers-=-1;
			GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, GetComponent->GetMaterial(0)->GetName());
		}
	}
	if (GetComponent == Seven)
	{
		if (AnswerN < RightA.Num() and RightA[AnswerN] == GetComponent->GetMaterial(0)->GetName())
		{
			RAnswers-=-1;
			GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, GetComponent->GetMaterial(0)->GetName());
		}
	}
	if (GetComponent == Eight)
	{
		if (AnswerN < RightA.Num() and RightA[AnswerN] == GetComponent->GetMaterial(0)->GetName())
		{
			RAnswers-=-1;
			GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, GetComponent->GetMaterial(0)->GetName());
		}
	}
	AnswerN++;
	if (AnswerN==3)
	{
		if (RAnswers==3)
		{
			UE_LOG(LogTemp, Warning, TEXT("You win"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("You lose"));
		}
	}

}

void APanal::PanalI(FString a, FString b, FString c)
{
	RightA.Empty();
	RightA.Add(a);
	RightA.Add(b);
	RightA.Add(c);
	
	for (int i = 0; i < Meshes.Num(); ++i)
	{
		k = FMath::RandRange(0,Meshes.Num()-1);
		OldTransform = Meshes[i]->GetComponentTransform();
		Meshes[i]->SetWorldTransform(Meshes[k]->GetComponentTransform());
		Meshes[k]->SetWorldTransform(OldTransform);
	}
	
}




