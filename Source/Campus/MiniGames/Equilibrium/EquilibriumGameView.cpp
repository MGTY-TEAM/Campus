#include "Campus/MiniGames/Equilibrium/EquilibriumGameView.h"
#include "Campus/MiniGames/Equilibrium/EquilibriumView.h"

AEquilibriumGameView::AEquilibriumGameView()
{
	PrimaryActorTick.bCanEverTick = true;
	bRunConstructionScriptOnDrag = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

	// ChildActorComponent = CreateDefaultSubobject<UChildActorComponent>("ChildActorComponent");
	// ChildActorComponent->SetupAttachment(GetRootComponent());
}

void AEquilibriumGameView::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	
	TArray<USceneComponent*> Components;
	SceneComponent->GetChildrenComponents(true, Components);
	for (const auto Component : Components)
	{
		if (Component)
		{
			Component->UnregisterComponent();
			Component->DestroyComponent();
		}
	}
	Components.Reset();
	
	if (UChildActorComponent* ChildActorComponent = Cast<UChildActorComponent>(AddComponentByClass(UChildActorComponent::StaticClass(),true, FTransform(), false)))
	{
		ChildActorComponent->RegisterComponent();
		
		ChildActorComponent->SetChildActorClass(EquilibriumViewClass);
		AEquilibriumView* Equilibrium = Cast<AEquilibriumView>(ChildActorComponent->GetChildActor());
		Equilibrium->CreateEquilibrium(Cups);
		ChildActorComponent->AttachToComponent(SceneComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);

		AddInstanceComponent(ChildActorComponent);
		UE_LOG(LogTemp, Warning, TEXT("Added EquilibriumViewInstance"));
	}
}

void AEquilibriumGameView::BeginPlay()
{
	Super::BeginPlay();
}

void AEquilibriumGameView::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
