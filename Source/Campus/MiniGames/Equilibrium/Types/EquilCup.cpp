
#include "Campus/MiniGames/Equilibrium/Types/EquilCup.h"

AEquilCup::AEquilCup()
{
	StaticMeshComponent->SetupAttachment(GetRootComponent());
}

void AEquilCup::AddWeight(int32_t NewWeight)
{
	if (GetCoordinates().empty()) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "No Coordinates");
	Weight = NewWeight;
	OnAttemptToAddWeight.Broadcast(GetCoordinates(), NewWeight);
}

void AEquilCup::RemoveWeight()
{
	Weight = 0;
	OnAttemptToRemoveWeight.Broadcast(GetCoordinates());
}

void AEquilCup::SetCoordinates(const std::vector<int32_t>& CoordinatesForSet)
{
	Coordinates = CoordinatesForSet;
}
