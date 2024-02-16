// Fill out your copyright notice in the Description page of Project Settings.


#include "PanalWidget.h"

#include "BinaryTree.h"
#include "PanalButtonsWidget.h"


class UWidgetBlueprint;
// Sets default values
APanalWidget::APanalWidget()
{
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Board"));
	CollisionMesh = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Mesh"));
	Origin = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Origin"));
	Answers = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Answers"));
	
	RootComponent = Origin;
	
	WidgetComponent->SetupAttachment(Origin);
	Mesh->SetupAttachment(Origin);
	CollisionMesh->SetupAttachment(Origin);
	Answers->SetupAttachment(Origin);
	
	CollisionMesh->SetNotifyRigidBodyCollision(true);

	FRandomStream(time(0));
}

FString APanalWidget::ToBinary(int32 num)
{
	int bin = 0, n = 1 , numOrg = num;
	FString stringbin = " ";
	
	while (num)
	{
		bin += (num % 2) * n;
		n *= 10;
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

// Called when the game starts or when spawned
void APanalWidget::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APanalWidget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APanalWidget::Interact(UActorComponent* InteractComponent, const FVector& InteractPoint,
	const FVector& InteractionNormal)
{
	if (InteractComponent==CollisionMesh)
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
	
		FirstAnswMesh =  FMath::RandRange(0, 7);
		SecondAnswMesh =  FMath::RandRange(0, 7);
		ThirdAnswMesh =  FMath::RandRange(0, 7);
	
		while (FirstAnswMesh == SecondAnswMesh)
		{
			SecondAnswMesh =  FMath::RandRange(0, 7);
		}
		while (SecondAnswMesh == ThirdAnswMesh || FirstAnswMesh == ThirdAnswMesh)
		{
			ThirdAnswMesh =  FMath::RandRange(0, 7);
		}
	
		ABinaryTree* Tree = Cast<ABinaryTree>(UGameplayStatics::GetActorOfClass(GetWorld(), ABinaryTree::StaticClass()));
	
		Tree->BinaryTreeI(FirstAnsw,SecondAnsw,ThirdAnsw ,FirstAnswMesh ,SecondAnswMesh ,ThirdAnswMesh);
		PanalI(FirstAnswMesh ,SecondAnswMesh ,ThirdAnswMesh);
		RandomWorkStart.Broadcast();
		UE_LOG(LogTemp, Warning, TEXT("Номера ответов  %d , %d , %d") , FirstAnswMesh ,SecondAnswMesh ,ThirdAnswMesh);
		Answers->SetText(FText::FromString(ToBinary(FirstAnsw)  + " " + ToBinary(SecondAnsw) + " " + ToBinary(ThirdAnsw) ));
	}
	
}

void APanalWidget::PanalI(int32 FirstMeshNumber, int32 SecondMeshNumber, int32 ThirdMeshNumber)
{
	RightAnswer.Empty();
	RightAnswer.Add(FirstMeshNumber);
	RightAnswer.Add(SecondMeshNumber);
	RightAnswer.Add(ThirdMeshNumber);
}

