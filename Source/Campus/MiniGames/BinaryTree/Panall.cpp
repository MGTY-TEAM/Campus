// Fill out your copyright notice in the Description page of Project Settings.


#include "Panall.h"

// Sets default values
APanall::APanall()
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
	Zero->Rename(TEXT("apple"));

	
	ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/Mesh/BinaryTree/ControlPanal/domofon__1__B1.domofon__1__B1'"));
	
//	Zero->SetStaticMesh(MeshAsset.Object);
	
	Zero->SetNotifyRigidBodyCollision(true);
//	Zero->SetCollisionProfileName(TEXT("BlockAll"));  // Устанавливаем профиль коллизии
	Zero->SetGenerateOverlapEvents(true);  

}
void APanall::Interact(UPrimitiveComponent* GetComponent, ABaseFirstPersonCharacter* SelfCharacter)
{

}


// Called when the game starts or when spawned
void APanall::BeginPlay()
{
	Super::BeginPlay();
	
}

