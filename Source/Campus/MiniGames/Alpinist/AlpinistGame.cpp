
#include "Campus/MiniGames/Alpinist/AlpinistGame.h"

#include "Components/StaticMeshcomponent.h"
#include "Campus/MiniGames/Alpinist/AlpinistIDEController.h"

AAlpinistGame::AAlpinistGame()
{
	PrimaryActorTick.bCanEverTick = true;

	TelegraphBaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("TelegraphBaseMeshComponent");
	SetRootComponent(TelegraphBaseMeshComponent);

	TelegraphShoulderMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("TelegraphShoulderMeshComponent");
	TelegraphShoulderMeshComponent->SetupAttachment(TelegraphBaseMeshComponent);

	AlpinistIDEController = CreateDefaultSubobject<UAlpinistIDEController>("AlpinistIDEController");
}

void AAlpinistGame::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAlpinistGame::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAlpinistGame::Interact(UActorComponent* InteractComponent, const FVector& InteractPoint, const FVector& InteractionNormal)
{
	IInteractable::Interact(InteractComponent, InteractPoint, InteractionNormal);

	UE_LOG(LogTemp, Display, TEXT("Alpinost Game Started"));
}

