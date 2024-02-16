// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Actor.h"
#include "MiniMinic.generated.h"

UCLASS()
class CAMPUS_API AMiniMinic : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AMiniMinic();
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UTextRenderComponent* Answer;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* Origin;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* Mesh;
protected:
	// Called when the game starts or when spawned

};
