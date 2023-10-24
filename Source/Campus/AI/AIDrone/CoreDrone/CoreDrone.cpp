// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreDrone.h"

#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"

ACoreDrone::ACoreDrone()
{
	PrimaryActorTick.bCanEverTick = true;
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Screen = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Screen"));
	Body->SetupAttachment(GetCapsuleComponent());
	Screen->SetupAttachment(Body);
}
