// Fill out your copyright notice in the Description page of Project Settings.


#include "BoardCell.h"

#include "BasePiece.h"


// Sets default values
ABoardCell::ABoardCell()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SceneComponent = CreateDefaultSubobject<USceneComponent>("Scene");
	StaticMeshComponent->OnClicked.AddDynamic(this, &ABoardCell::OnClicked);

	SceneComponent = RootComponent;
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

void ABoardCell::SetUpCell(TPair<int, int> Pos, ABasePiece* BasePiece, UMaterialInstance* PieceMaterial)
{
	CellPos = Pos;
	Piece = BasePiece;
	if (Piece)
	{
		UE_LOG(LogTemp, Error, TEXT("%s"), *Piece->GetName());
		Piece->StaticMeshComponent->SetMaterial(0, PieceMaterial);
	}
}

void ABoardCell::SetUpColor(UMaterialInstance* MaterialInstance, bool bColorWhite)
{
	if (StaticMeshComponent)
	{
		StaticMeshComponent->SetMaterial(0, MaterialInstance);
		bWhite = bColorWhite;
	}
}

void ABoardCell::Click()
{
	UE_LOG(LogTemp, Warning, TEXT("BoardCell Click"));
	OnCellClicked.Broadcast(CellPos.Get<0>(),CellPos.Get<1>());
}

void ABoardCell::PlacePiece(ABasePiece* NewPiece)
{
	Piece = NewPiece;
}


