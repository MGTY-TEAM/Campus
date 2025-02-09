
#include "Campus/MiniGames/Equilibrium/Types/AEquilElement.h"

AAEquilElement::AAEquilElement()
{
	PrimaryActorTick.bCanEverTick = true;
	
	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMeshComponent->SetupAttachment(GetRootComponent());

	StaticMeshComponentForArm = CreateDefaultSubobject<UStaticMeshComponent>("Arm");
	StaticMeshComponentForArm->SetupAttachment(GetRootComponent());
}

void AAEquilElement::SetLeftChild(AAEquilElement* Element)
{
	if (Element)
	{
		LeftChild = Element;
	}
}

void AAEquilElement::SetRightChild(AAEquilElement* Element)
{
	if (Element)
	{
		RightChild = Element;
	}
}

