// Fill out your copyright notice in the Description page of Project Settings.


#include "PanalWidget.h"

#include "PanalButtonsWidget.h"


class UWidgetBlueprint;
// Sets default values
APanalWidget::APanalWidget()
{
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
 
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Board"));


	Origin = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Origin"));
	RootComponent = Origin;
	WidgetComponent->SetupAttachment(Origin);
	Mesh->SetupAttachment(Origin);

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

void APanalWidget::PanalI(int32 FirstMeshNumber, int32 SecondMeshNumber, int32 ThirdMeshNumber)
{
	RightAnswer.Empty();
	RightAnswer.Add(FirstMeshNumber);
	RightAnswer.Add(SecondMeshNumber);
	RightAnswer.Add(ThirdMeshNumber);
}

