// Fill out your copyright notice in the Description page of Project Settings.


#include "BoardCell.h"


// Sets default values
ABoardCell::ABoardCell()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SceneComponent = CreateDefaultSubobject<USceneComponent>("Scene");
	StaticMeshComponent->OnClicked.AddDynamic(this,&ABoardCell::OnClicked);
}
void ABoardCell::OnClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	OnCellClicked.Broadcast(CellPos.Get<0>(), CellPos.Get<1>());
}
// Called when the game starts or when spawned
void ABoardCell::BeginPlay()
{
	Super::BeginPlay();
}

void ABoardCell::SetUpCell(UMaterialInstance* Material, TPair<int, int> Pos)
{
	if (StaticMeshComponent)
	{
		StaticMeshComponent->SetMaterial(0, Material);
	}
	CellPos = Pos;
}

void ABoardCell::Click()
{
	OnCellClicked.Broadcast(CellPos.Get<0>(),CellPos.Get<1>());
}

void ABoardCell::PlacePiece(ABasePiece* NewPiece)
{
	Piece = NewPiece;
}


