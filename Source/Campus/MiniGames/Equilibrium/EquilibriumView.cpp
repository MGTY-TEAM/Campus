
#include "Campus/MiniGames/Equilibrium/EquilibriumView.h"
#include "Campus/Libraries/CampusUtils.h"
#include "Campus/MiniGames/Equilibrium/Types/EquilCup.h"
#include "Campus/MiniGames/Equilibrium/Types/EquilNode.h"
#include "Campus/MiniGames/Equilibrium/EquilibriumViewModelComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogEquilView, All, All);

AEquilibriumView::AEquilibriumView()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

	EquilibriumViewModelComponent = CreateDefaultSubobject<UEquilibriumViewModelComponent>("EquilibriumViewModel");
}

void AEquilibriumView::CreateEquilibrium(const TArray<FString>& CupsCoor)
{
	if (!SceneComponent) return;
	
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
	
	CupsCoo = CupsCoor;
	
	if (CupsCoo.IsEmpty()) return;
	for (auto CupCoo : CupsCoo)
	{
		if (CupCoo.IsEmpty() || !CupCoo.IsNumeric() || !CampusUtils::IsBinaryNumber(CupCoo)) return;
	}
	
	if (UChildActorComponent* ChildActorComponent = Cast<UChildActorComponent>(AddComponentByClass(UChildActorComponent::StaticClass(), true, FTransform(), false)))
	{
		ChildActorComponent->RegisterComponent();
		ChildActorComponent->SetChildActorClass(SpawnableNodeClass);
		ChildActorComponent->AttachToComponent(SceneComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
		ChildActorComponent->SetRelativeLocation(SceneComponent->GetComponentLocation());

		AddInstanceComponent(ChildActorComponent);
		Root = Cast<AEquilNode>(ChildActorComponent->GetChildActor());

		if (Root->GetStaticMesh())
		{
			Root->GetStaticMesh()->SetStaticMesh(StaticMeshForRootNode);
			Root->GetStaticMesh()->SetRelativeLocation(Root->GetStaticMesh()->GetRelativeLocation() - FVector(0.f, 0.f, 5.25f));
			if (const AEquilNode* RootNode = Cast<AEquilNode>(Root))
			{
				RootNode->GetPositionLeft()->SetRelativeLocation(RootNode->GetPositionLeft()->GetRelativeLocation() + FVector(-6.75f, 0.f, 0.f));
				RootNode->GetPositionRight()->SetRelativeLocation(RootNode->GetPositionRight()->GetRelativeLocation() + FVector(6.75f, 0.f, 0.f));
			}
		}
		
		if (Root->GetStaticMeshForArm())
		{
			Root->GetStaticMeshForArm()->SetStaticMesh(StaticMeshForRootArm);
			Root->GetStaticMeshForArm()->SetRelativeLocation(Root->GetStaticMeshForArm()->GetRelativeLocation()+ FVector(0.f, 0.f, -30.125f));
		}
	}
	
	for (auto CupCoo : CupsCoo)
	{
		if (CupCoo.IsEmpty()) continue;

		int16 Index = 0;
		const int16 Count = CupCoo.Len();

		AEquilNode* Current = Cast<AEquilNode>(Root);
		
		for (const auto Place : CupCoo)
		{
			if (++Index == Count) continue;
			if (!Current) return;
			
			if (FChar::ConvertCharDigitToInt(Place))
			{
				if (const UChildActorComponent* ChildActorComponent = CreateNode(Current, Current->GetRightChild(), Current->GetPositionRight()))
				{
					Current->SetRightChild(Cast<AEquilNode>(ChildActorComponent->GetChildActor()));
				}
				Current = Cast<AEquilNode>(Current->GetRightChild());
			}
			else
			{
				if (const UChildActorComponent* ChildActorComponent = CreateNode(Current, Current->GetLeftChild(), Current->GetPositionLeft()))
				{
					Current->SetLeftChild(Cast<AEquilNode>(ChildActorComponent->GetChildActor()));
				}
				Current = Cast<AEquilNode>(Current->GetLeftChild());
			}
		}
		
		if (FChar::ConvertCharDigitToInt(CupCoo[CupCoo.Len() - 1]))
		{
			if (const UChildActorComponent* ChildActorComponent = CreateCup(Current->GetPositionRight(), CupCoo))
			{
				Current->SetRightChild(Cast<AEquilCup>(ChildActorComponent->GetChildActor()));
			}
		}
		else
		{
			if (const UChildActorComponent* ChildActorComponent = CreateCup(Current->GetPositionLeft(), CupCoo))
			{
				Current->SetLeftChild(Cast<AEquilCup>(ChildActorComponent->GetChildActor()));
			}
		}
	}
}

void AEquilibriumView::BeginPlay()
{
	Super::BeginPlay();

	if (EquilibriumViewModelComponent)
	{
		EquilibriumViewModelComponent->CreateModelInstance(CampusUtils::TArrayOfFStringToVectorOfVectorOfInt(CupsCoo));
		EquilibriumViewModelComponent->OnChangeStates.AddUObject(this, &AEquilibriumView::CalculateRotation);
	}
	SetCoordinatesForCups();
}

void AEquilibriumView::AddCupToArrayOfCups(AEquilCup* NewCup)
{
	if (NewCup)
	{
		Cups.Add(NewCup);
	}
}

void AEquilibriumView::SetCoordinatesForCups()
{
	int index = 0;
	for (auto Cup : Cups)
	{
		Cup->SetCoordinates(CampusUtils::FStringToVectorOfInt(CupsCoo[index++]));
	}
}

void AEquilibriumView::SetNewStates(AEquilNode* RootNode, std::vector<EquilibriumTypes::ENodeRotationState>& RotationStates)
{
	if (RotationStates.empty()) return;

	RootNode->SetNewState(RotationStates.front());
	RotationStates.erase(RotationStates.begin());
	
	if (AEquilNode* LeftNodeRoot = Cast<AEquilNode>(RootNode->GetLeftChild()))
	{
		SetNewStates(LeftNodeRoot, RotationStates);
	}
	if (AEquilNode* RightNodeRoot = Cast<AEquilNode>(RootNode->GetRightChild()))
	{
		SetNewStates(RightNodeRoot, RotationStates);
	}
}

void AEquilibriumView::CalculateRotation(const std::vector<EquilibriumTypes::ENodeRotationState>& RotationStates)
{
	if (Root)
	{
		std::vector<EquilibriumTypes::ENodeRotationState> VectorToDelete = RotationStates;
		SetNewStates(Cast<AEquilNode>(Root), VectorToDelete);
		CalculateRotation(Root);
	}
}

void AEquilibriumView::CalculateRotation(AAEquilElement* RootElem)
{
	if (AEquilNode* RootNode = Cast<AEquilNode>(RootElem))
	{
		if (RootNode->GetLeftChild())
		{
			CalculateRotation(RootNode->GetLeftChild());
		}
		if (RootNode->GetRightChild())
		{
			CalculateRotation(RootNode->GetRightChild());
		}
		
		switch(RootNode->GetRotationState())
		{
		case EquilibriumTypes::NRS_Left:
			RootNode->CalculateRotation(FRotator(15.f, 0, 0));
			break;
		case EquilibriumTypes::NRS_Right:
			RootNode->CalculateRotation(FRotator(-15.f, 0, 0));
			break;
		case EquilibriumTypes::NRS_Stable:
			RootNode->CalculateRotation(FRotator(0.f, 0, 0));
			break;
		default:
			break;
		}
	}
}

UChildActorComponent* AEquilibriumView::CreateNode(AEquilNode* Current, const AAEquilElement* Child, USceneComponent* Position)
{
	if (Child == nullptr)
	{
		if (UChildActorComponent* ChildActorComponent = Cast<UChildActorComponent>(AddComponentByClass(UChildActorComponent::StaticClass(), true, FTransform(), false)))
		{
			ChildActorComponent->RegisterComponent();
			ChildActorComponent->SetChildActorClass(SpawnableNodeClass);
			ChildActorComponent->GetChildActor()->AttachToComponent(Position, FAttachmentTransformRules::SnapToTargetIncludingScale);
			ChildActorComponent->SetRelativeLocation(Position->GetComponentLocation());
			ChildActorComponent->GetChildActor()->SetActorRelativeRotation(FRotator(0, 90, 0));

			AddInstanceComponent(ChildActorComponent);
			return ChildActorComponent;
		}
		return nullptr;
	}
	return nullptr;
}

UChildActorComponent* AEquilibriumView::CreateCup(USceneComponent* Position, const FString& CupCoo)
{
	if (UChildActorComponent* ChildActorComponent = Cast<UChildActorComponent>(AddComponentByClass(UChildActorComponent::StaticClass(), true, FTransform(), false)))
	{
		ChildActorComponent->RegisterComponent();
		ChildActorComponent->SetChildActorClass(SpawnableCupClass);
		ChildActorComponent->GetChildActor()->AttachToComponent(Position, FAttachmentTransformRules::SnapToTargetIncludingScale);
		ChildActorComponent->SetRelativeLocation(Position->GetComponentLocation());

		AddInstanceComponent(ChildActorComponent);
				
		if (AEquilCup* Cup = Cast<AEquilCup>(ChildActorComponent->GetChildActor()))
		{
			Cup->SetCoordinates(CampusUtils::FStringToVectorOfInt(CupCoo));
			Cups.Add(Cup);
			return ChildActorComponent;
		}
		return nullptr;
	}
	return nullptr;
}
