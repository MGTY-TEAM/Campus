// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItemVisual.h"
#include "UObject/UObjectGlobals.h"
#include "Campus/Core/BaseCharacter/BaseFirstPersonCharacter.h"


// Sets default values
AInventoryItemVisual::AInventoryItemVisual()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("RootScene");
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	
	StaticMeshComponent->SetupAttachment(RootComponent);
	
	InventoryItem = NewObject<UInventoryItem>();
	InventoryItem->StaticMeshComponent = StaticMeshComponent;
}

// Called when the game starts or when spawned
void AInventoryItemVisual::BeginPlay()
{
	Super::BeginPlay();
}

UInventoryItem* AInventoryItemVisual::PickUp()
{
	UInventoryItem* CopyInventoryItem = NewObject<UInventoryItem>();
	DuplicateObject(InventoryItem, CopyInventoryItem);
	Destroy();
	return CopyInventoryItem;
}

// Called every frame
void AInventoryItemVisual::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AInventoryItemVisual::Interact(AActor* InteractedActor, AActor* SelfCharacter){}
void AInventoryItemVisual::EndInteract(AActor* FocusActor, AActor* SelfCharacter){}
