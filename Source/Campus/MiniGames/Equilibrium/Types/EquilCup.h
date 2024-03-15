
#pragma once

#include "CoreMinimal.h"
#include "Campus/MiniGames/Equilibrium/Types/AEquilElement.h"
#include "EquilCup.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAttemptToAddWeight, const std::vector<int32_t>&, int32_t);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnAttemptToRemoveWeight, const std::vector<int32_t>&);

class UPickupSocketComponent;

UCLASS()
class CAMPUS_API AEquilCup : public AAEquilElement
{
	GENERATED_BODY()

public:
	AEquilCup();

	UFUNCTION()
	void AddWeight(AInventoryActor* InventoryActor);
	UFUNCTION()
	void RemoveWeight();

	std::vector<int32_t> GetCoordinates() const { return Coordinates; }
	void SetCoordinates(const std::vector<int32_t>& CoordinatesForSet);
	
	FOnAttemptToAddWeight OnAttemptToAddWeight;
	FOnAttemptToRemoveWeight OnAttemptToRemoveWeight;
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, Category = "Equilibrium")
	UPickupSocketComponent* PickupSocketComponent;
private:
	std::vector<int32_t> Coordinates;
};
