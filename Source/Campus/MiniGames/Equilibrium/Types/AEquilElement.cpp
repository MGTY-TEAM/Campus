
#include "Campus/MiniGames/Equilibrium/Types/AEquilElement.h"

AAEquilElement::AAEquilElement()
{
	PrimaryActorTick.bCanEverTick = true;
	
	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMeshComponent->SetupAttachment(GetRootComponent());
}

void AAEquilElement::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAEquilElement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAEquilElement::SetLeftChild(AAEquilElement* Element)
{
	LeftChild = Element;
}

void AAEquilElement::SetRightChild(AAEquilElement* Element)
{
	RightChild = Element;
}

