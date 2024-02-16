// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniMinic.h"


// Sets default values
AMiniMinic::AMiniMinic()
{
	Answer = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Answers"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Monic"));
	Origin = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Origin"));

	Origin->SetupAttachment(RootComponent);
	Mesh->SetupAttachment(Origin);
	Answer->SetupAttachment(Origin);
}

// Called when the game starts or when spawned

