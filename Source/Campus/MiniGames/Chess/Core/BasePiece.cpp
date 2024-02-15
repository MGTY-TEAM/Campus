// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePiece.h"




// Sets default values
ABasePiece::ABasePiece()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("PieceMesh");
}


// Called when the game starts or when spawned
void ABasePiece::BeginPlay()
{
	Super::BeginPlay();
	
}


TMap<int, int> ABasePiece::GetPossibleMoves()
{
	return TMap<int, int>();
}

void ABasePiece::SetUpColor(bool bisWhite, UMaterialInstance* White, UMaterialInstance* Black)
{
	bWhite = bisWhite;
	if (bWhite)
	{
		StaticMeshComponent->SetMaterial(0, White);
	}
	else
	{
		StaticMeshComponent->SetMaterial(0, Black);
	}
}

