// Fill out your copyright notice in the Description page of Project Settings.


#include "PanalRandom.h"
#include "Engine/World.h"  
#include "BinaryTree.h"
#include "GPUSkinCache.h"
#include "NavigationSystemTypes.h"


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


void APanalRandom::Interact(AActor* InteractedActor, AActor* SelfCharacter)
{
	UE_LOG(LogTemp, Warning, TEXT("Generate Numbers") );

	FirstAnsw = GenerateNum();
	SecondAnsw = GenerateNum();
	ThirdAnsw = GenerateNum();
	
	UE_LOG(LogTemp, Warning, TEXT("Give") );
	
	
	while (FirstAnsw == SecondAnsw)
	{
		SecondAnsw = GenerateNum();
	}
	while (SecondAnsw == ThirdAnsw || FirstAnsw == ThirdAnsw)
	{
		ThirdAnsw = GenerateNum();
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

	//ABinaryTree* PanelR = NewObject<ABinaryTree>(GetWorld() , TEXT("PanalR"));

//	ABinaryTree PanelR = Cast<ABinaryTree>(GetWorld()->GetCurrentLevel()->GetAc); 
	
	PanelR->BinaryTreeI(FirstAnsw,SecondAnsw,ThirdAnsw ,FirstAnswString ,SecondAnswString ,ThirdAnswString);
	
	APanal* Panal = NewObject<APanal>(GetWorld(), TEXT("Apnal"));
	
	Panal->PanalI( FirstAnswString ,SecondAnswString ,ThirdAnswString);
	
	
	
	
	TextRender->SetText(FText::FromString(ToBinary(FirstAnsw)  + " " + ToBinary(SecondAnsw) + " " + ToBinary(ThirdAnsw) + " " + FirstAnswString + " "  + SecondAnswString + " " + ThirdAnswString));
	
}




int32 APanalRandom::GenerateNum()
{
	int32 num = FMath::RandRange(0, 7);
	return num;
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









