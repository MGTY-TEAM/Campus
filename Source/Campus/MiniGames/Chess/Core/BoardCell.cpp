// Fill out your copyright notice in the Description page of Project Settings.


#include "BoardCell.h"


// Sets default values
ABoardCell::ABoardCell()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SceneComponent = CreateDefaultSubobject<USceneComponent>("Scene");

}

// Called when the game starts or when spawned
void ABoardCell::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABoardCell::SetMaterial(UMaterialInstance* Material)
{
	if (StaticMeshComponent)
	{
		StaticMeshComponent->SetMaterial(0, Material);
	}
}

void ABoardCell::PlacePiece(ABasePiece* NewPiece)
{
	Piece = NewPiece;
}


