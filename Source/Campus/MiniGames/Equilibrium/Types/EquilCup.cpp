
#include "Campus/MiniGames/Equilibrium/Types/EquilCup.h"
#include "Campus/Inventory/PickupSocketComponent.h"
#include "Campus/MiniGames/Equilibrium/Types/EquilCargo.h"

AEquilCup::AEquilCup()
{
	StaticMeshComponent->SetupAttachment(GetRootComponent());

	PickupSocketComponent = CreateDefaultSubobject<UPickupSocketComponent>("PickupSocketComponent");
	PickupSocketComponent->SetupAttachment(GetRootComponent());
	PickupSocketComponent->SetAttachmentScene(GetRootComponent());
}

void AEquilCup::BeginPlay()
{
	Super::BeginPlay();

	if (PickupSocketComponent)
	{
		PickupSocketComponent->OnPickupPlaced.BindDynamic(this, &AEquilCup::AddWeight);
		PickupSocketComponent->OnPickupRemoved.BindDynamic(this, &AEquilCup::RemoveWeight);
	}
}

void AEquilCup::AddWeight(AInventoryActor* InventoryActor)
{
	if (const AEquilCargo* Cargo = Cast<AEquilCargo>(InventoryActor))
	{
		OnAttemptToAddWeight.Broadcast(GetCoordinates(), Cargo->GetWeight());
	}
}

void AEquilCup::RemoveWeight()
{
	OnAttemptToRemoveWeight.Broadcast(GetCoordinates());
}

void AEquilCup::SetCoordinates(const std::vector<int32_t>& CoordinatesForSet)
{
	Coordinates = CoordinatesForSet;
}
