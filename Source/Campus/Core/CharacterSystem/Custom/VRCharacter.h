#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "VRCharacter.generated.h"


UCLASS()
class CAMPUS_API AVRCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AVRCharacter();

protected:

	UPROPERTY(VisibleAnywhere, Category= "Components")
	USceneComponent* VROriginComponent;

	UPROPERTY(EditDefaultsOnly, Category= "VR")
	bool bPositionalHeadTracking;

	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* CameraComponent;


	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
