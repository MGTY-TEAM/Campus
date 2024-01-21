// Fill out your copyright notice in the Description page of Project Settings.


#include "PanalRandom.h"
#include "Engine/World.h"  
#include "BinaryTree.h"
#include "GPUSkinCache.h"
#include "NavigationSystemTypes.h"
#include "Panal.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
APanalRandom::APanalRandom()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	TextRender = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Text"));

	CollisionMesh = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Mesh"));

	RootComponent = CollisionMesh;
	TextRender->SetupAttachment(CollisionMesh);
	
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	FRandomStream(time(0));
}

// Called when the game starts or when spawned
void APanalRandom::BeginPlay()
{
	Super::BeginPlay();
}


void APanalRandom::Interact(UActorComponent* InteractComponent, const FVector& InteractPoint, const FVector& InteractionNormal)
{
	UE_LOG(LogTemp, Warning, TEXT("Generate Numbers"));

	FirstAnsw =  FMath::RandRange(0, 7);
	SecondAnsw =  FMath::RandRange(0, 7);
	ThirdAnsw =  FMath::RandRange(0, 7);
	
	while (FirstAnsw == SecondAnsw)
	{
		SecondAnsw =  FMath::RandRange(0, 7);
	}
	while (SecondAnsw == ThirdAnsw || FirstAnsw == ThirdAnsw)
	{
		ThirdAnsw =  FMath::RandRange(0, 7);
	}
	
	FirstAnswString = AllAnswString[FMath::RandRange(0,7)];
	SecondAnswString = AllAnswString[FMath::RandRange(0,7)];
	ThirdAnswString = AllAnswString[FMath::RandRange(0,7)];

	while (FirstAnswString == SecondAnswString)
	{
		SecondAnswString = AllAnswString[FMath::RandRange(0,7)];
	}
	while (SecondAnswString == ThirdAnswString || FirstAnswString == ThirdAnswString)
	{
		ThirdAnswString = AllAnswString[FMath::RandRange(0,7)];
	}
	
	ABinaryTree* Tree = Cast<ABinaryTree>(UGameplayStatics::GetActorOfClass(GetWorld(), ABinaryTree::StaticClass()));
	APanal* Panal = Cast<APanal>(UGameplayStatics::GetActorOfClass(GetWorld(), APanal::StaticClass()));
	
	Tree->BinaryTreeI(FirstAnsw,SecondAnsw,ThirdAnsw ,FirstAnswString ,SecondAnswString ,ThirdAnswString);
	Panal->PanalI( FirstAnswString ,SecondAnswString ,ThirdAnswString);
	
	
	TextRender->SetText(FText::FromString(ToBinary(FirstAnsw)  + " " + ToBinary(SecondAnsw) + " " + ToBinary(ThirdAnsw) + " " + FirstAnswString + " "  + SecondAnswString + " " + ThirdAnswString));
	
}


FString APanalRandom::ToBinary(int32 num)
{
	int bin = 0, k = 1 , numOrg = num;
	FString stringbin = " ";
	
	while (num)
	{
		bin += (num % 2) * k;
		k *= 10;
		num /= 2;
	}
	
	if (numOrg==1 || numOrg==0)
	{
		stringbin = "00"  + FString::FromInt(bin);
	}
	if (numOrg==2 || numOrg==3)
	{
		stringbin = "0"  + FString::FromInt(bin);
	}
	if (numOrg>=4 and numOrg<=7)
	{
		stringbin = FString::FromInt(bin);
	}
	return stringbin;
}









