// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PanalButton.generated.h"



UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CAMPUS_API UPanalButton : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPanalButton();
	


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=StaticMesh, meta=(AllowPrivateAccess="true"))
	UStaticMesh* Button;



protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
