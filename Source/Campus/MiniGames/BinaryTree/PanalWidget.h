// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Campus/Interfaces/Interaction/Interactable.h"
#include "Campus/Interfaces/MiniGames/BinaryFruit/BinaryFruit.h"
#include "Components/BoxComponent.h"
#include "Components/Widget.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"
#include "PanalWidget.generated.h"

UCLASS()
class CAMPUS_API APanalWidget : public AActor , public IBinaryFruit , public IInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APanalWidget();

	int32 FirstAnsw = 0;
	int32 SecondAnsw = 0;
	int32 ThirdAnsw = 0;
	
	int32 FirstAnswMesh = 0;
	int32 SecondAnswMesh = 0;
	int32 ThirdAnswMesh = 0;
	FString ToBinary(int32 num);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UWidgetComponent* WidgetComponent;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY()
	UStaticMeshComponent* Origin;
	UPROPERTY(EditAnywhere, Category = "Mesh")
	UBoxComponent* CollisionMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	UTextRenderComponent* Answers;
	
	int32 k = 0;
	virtual void Interact(UActorComponent* InteractComponent, const FVector& InteractPoint, const FVector& InteractionNormal) override;
	
	virtual void PanalI(int32 FirstMeshNumber, int32 SecondMeshNumber, int32 ThirdMeshNumber) override;
public:
	UPROPERTY(BlueprintAssignable , BlueprintCallable , BlueprintReadWrite)
	FRandom RandomWorkStart;
	UPROPERTY(BlueprintAssignable , BlueprintCallable , BlueprintReadWrite)
	FRandom RandomWorkEnd;
	UPROPERTY(BlueprintAssignable , BlueprintCallable , BlueprintReadWrite)
	FRandom StartTimer;
	TArray<int32> RightAnswer;
};
