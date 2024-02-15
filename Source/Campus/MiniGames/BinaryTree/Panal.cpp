// Fill out your copyright notice in the Description page of Project Settings.


#include "Panal.h"

#include "AsyncTreeDifferences.h"


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
	DeleteButton = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DeleteButton"));
	AnswerButton = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AnswerButton"));

	RootComponent = Root;

	Meshes.Add(Zero);
	Meshes.Add(One);
	Meshes.Add(Two);
	Meshes.Add(Three);
	Meshes.Add(Four);
	Meshes.Add(Five);
	Meshes.Add(Six);
	Meshes.Add(Seven);
	Meshes.Add(Eight);

	for (int i = 0; i < Meshes.Num(); ++i)
	{
		// Attach to root
		Meshes[i]->SetupAttachment(Root);
		// Setup collision
		Meshes[i]->SetNotifyRigidBodyCollision(true);
		Meshes[i]->SetCollisionProfileName(TEXT("BlockAll"));
	}

	DeleteButton->SetupAttachment(Root);
	DeleteButton->SetNotifyRigidBodyCollision(true);
	DeleteButton->SetCollisionProfileName(TEXT("BlockAll"));

	AnswerButton->SetupAttachment(Root);
	AnswerButton->SetNotifyRigidBodyCollision(true);
	AnswerButton->SetCollisionProfileName(TEXT("BlockAll"));

	ConstructorHelpers::FObjectFinder<UStaticMesh>PanalRoot(TEXT("/Script/Engine.StaticMesh'/Game/Mesh/BinaryTree/ControlPanal/domofon__1__Body.domofon__1__Body'"));
	
	if (PanalRoot.Succeeded())
	{
		Root->SetStaticMesh(PanalRoot.Object);
	}
}

// Called when the game starts or when spawned
void APanal::BeginPlay()
{
	Super::BeginPlay();
}


void APanal::SetupOldLocationAndAnsw()
{
	// Setup Buttons on right plase
	for (int i = 0; i < UsedMeshes.Num(); ++i)
	{
		FVector ComponentLocationNew = UsedMeshes[i]->GetComponentLocation();
		ComponentLocationNew.X = ComponentLocationNew.X - 3;
		UsedMeshes[i]->SetWorldLocation(ComponentLocationNew);
		AnswerNumber = 0;
		RightAnswers = 0;
	}
	UsedMeshes.Empty();
}

void APanal::Interact(UActorComponent* InteractComponent, const FVector& InteractPoint,
	const FVector& InteractionNormal)
{
	if (UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(InteractComponent))
	{
		// Set Location For Button
		if (PrimitiveComponent != AnswerButton and PrimitiveComponent != DeleteButton)
		{
			if (UsedMeshes.Contains(PrimitiveComponent))
			{
			}
			else
			{
				FVector ComponentLocation = PrimitiveComponent->GetComponentLocation();
				ComponentLocation.X = ComponentLocation.X + 3;
				PrimitiveComponent->SetWorldLocation(ComponentLocation);
				// Get Component what have vew location
				UsedMeshes.Add(PrimitiveComponent);
			}
		}
	
		// Add Answer when Answer True
		if (AnswerNumber<=3)
		{
			if (Meshes.Contains(PrimitiveComponent))
			{
				if (Meshes[RightAnswer[AnswerNumber]] == PrimitiveComponent)	
				{
					RightAnswers++;
				
					UE_LOG(LogTemp, Warning, TEXT("AnswerButton works %d ") , RightAnswers );
				}
			}
		}

		AnswerNumber++;
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::FromInt(AnswerNumber));
	
		if (PrimitiveComponent == AnswerButton)
		{
			if (RightAnswers == 3)
			{
				UE_LOG(LogTemp, Warning, TEXT("You win"));
				//Execute.ExecuteIfBound();
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("You lose"));
			}
			// Setup Buttons on right plase
			SetupOldLocationAndAnsw();
		}
	
		if (PrimitiveComponent == DeleteButton)
		{
			SetupOldLocationAndAnsw();
		}

		// Reset if Answer too much
		if (AnswerNumber==4)
		{
			SetupOldLocationAndAnsw();
		}
	}
	
}

void APanal::PanalI(int32 FirstMeshNumber, int32 SecondMeshNumber, int32 ThirdMeshNumber)
{
	RightAnswer.Empty();
	RightAnswer.Add(FirstMeshNumber);
	RightAnswer.Add(SecondMeshNumber);
	RightAnswer.Add(ThirdMeshNumber);

	
	for (int i = 0; i < Meshes.Num(); ++i)
	{
		k = FMath::RandRange(0,Meshes.Num()-1);
		OldTransform = Meshes[i]->GetComponentTransform();
		Meshes[i]->SetWorldTransform(Meshes[k]->GetComponentTransform());
		Meshes[k]->SetWorldTransform(OldTransform);
	}
}
