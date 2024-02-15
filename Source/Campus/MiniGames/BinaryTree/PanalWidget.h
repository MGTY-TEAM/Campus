// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Values.h"
#include "Campus/Interfaces/MiniGames/BinaryFruit/BinaryFruit.h"
#include "Components/Widget.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"
#include "PanalWidget.generated.h"

UCLASS()
class CAMPUS_API APanalWidget : public AActor , public IBinaryFruit
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APanalWidget();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UWidgetComponent* WidgetComponent;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY()
	UStaticMeshComponent* Origin;

	TArray<int32> RightAnswer;
	int32 k = 0;
	virtual void PanalI(int32 FirstMeshNumber, int32 SecondMeshNumber, int32 ThirdMeshNumber) override;
};
