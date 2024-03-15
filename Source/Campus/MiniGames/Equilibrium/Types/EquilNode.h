
#pragma once

#include "CoreMinimal.h"
#include "Campus/MiniGames/Equilibrium/Types/AEquilElement.h"
#include "Campus/MiniGames/Equilibrium/Core/EquilibriumTypes.h"
#include "EquilNode.generated.h"

UCLASS()
class CAMPUS_API AEquilNode : public AAEquilElement
{
	GENERATED_BODY()

public:
	AEquilNode();

	virtual void CalculateRotation(FRotator DesiredRotationToSet);
	EquilibriumTypes::ENodeRotationState GetRotationState() const { return RotationState; }

	USceneComponent* GetPositionLeft() const { return PositionLeft; }
	USceneComponent* GetPositionRight() const { return PositionRight; }

	void SetNewState(const EquilibriumTypes::ENodeRotationState& NewRotationState);
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USceneComponent* PositionLeft;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USceneComponent* PositionRight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USceneComponent* PositionAroundRotation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = 0.f, ClampMAx = 10.f))
	float InterpSpeedTime = 5.f;

public:
	virtual void Tick(float DeltaTime) override;

private:
	EquilibriumTypes::ENodeRotationState RotationState;
	FRotator DesiredRotation = FRotator();
	FRotator NormalRotation = FRotator();
	FRotator NormalLeftRotation = FRotator();
	FRotator NormalRightRotation = FRotator();
	
	void CalculateRotation(float DeltaTime) const;
};
