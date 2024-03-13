#include "Campus/MiniGames/Equilibrium/EquilibriumView.h"
#include "Campus/MiniGames/Equilibrium/Types/EquilCup.h"
#include "Campus/MiniGames/Equilibrium/Types/EquilNode.h"
#include "Campus/MiniGames/Equilibrium/EquilibriumGameView.h"
#include "Campus/MiniGames/Equilibrium/EquilibriumViewModelComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogEquilView, All, All);

AEquilibriumView::AEquilibriumView()
{
	PrimaryActorTick.bCanEverTick = true;
	bRunConstructionScriptOnDrag = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

	EquilibriumViewModelComponent = CreateDefaultSubobject<UEquilibriumViewModelComponent>("EquilibriumViewModel");
}

void AEquilibriumView::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	
}

void AEquilibriumView::CreateEquilibrium(const TArray<FString>& CupsCoor)
{
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
		if (CupCoo.IsEmpty()) return;
	}
	
	if (UChildActorComponent* ChildActorComponent = Cast<UChildActorComponent>(AddComponentByClass(UChildActorComponent::StaticClass(), true, FTransform(), false)))
	{
		ChildActorComponent->RegisterComponent();

		ChildActorComponent->SetChildActorClass(SpawnableNodeClass);
		
		ChildActorComponent->AttachToComponent(SceneComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);

		UE_LOG(LogTemp, Warning, TEXT("Added Root For EquilibriumViewInstance"));

		ChildActorComponent->SetRelativeLocation(SceneComponent->GetRelativeLocation());

		AddInstanceComponent(ChildActorComponent);
		Root = Cast<AEquilNode>(ChildActorComponent->GetChildActor());
	}
	
	for (auto CupCoo : CupsCoo)
	{
		if (CupCoo.IsEmpty()) continue;

		std::vector<int32_t> CupCooInt = FStringToVectorOfInt(CupCoo);
		int16 Index = 0;
		const int16 Count = CupCoo.Len();
		
		UE_LOG(LogTemp, Warning, TEXT("foreach Cups"));
		AEquilNode* Current = Cast<AEquilNode>(Root);
		
		for (const auto Place : CupCoo)
		{
			UE_LOG(LogTemp, Warning, TEXT("foreach Cup"));
			if (++Index == Count) continue;
			
			if (FChar::ConvertCharDigitToInt(Place))
			{
				if (Current->GetRightChild() == nullptr)
				{
					if (UChildActorComponent* ChildActorComponent = Cast<UChildActorComponent>(AddComponentByClass(UChildActorComponent::StaticClass(), true, FTransform(), false)))
					{
						ChildActorComponent->RegisterComponent();

						ChildActorComponent->SetChildActorClass(SpawnableNodeClass);

						// ChildActorComponent->AttachToComponent(Current->GetPositionRight(), FAttachmentTransformRules::SnapToTargetIncludingScale);
						// ChildActorComponent->AttachToComponent(SceneComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
						ChildActorComponent->GetChildActor()->AttachToComponent(Current->GetPositionRight(), FAttachmentTransformRules::SnapToTargetIncludingScale);

						UE_LOG(LogTemp, Warning, TEXT("Added Node For EquilibriumViewInstance"));

						ChildActorComponent->SetRelativeLocation(Current->GetPositionRight()->GetComponentLocation());
						// ChildActorComponent->SetRelativeRotation(FRotator(0, 90, 0));
						ChildActorComponent->GetChildActor()->SetActorRelativeRotation(FRotator(0, 90, 0));

						AddInstanceComponent(ChildActorComponent);
						Current->SetRightChild(Cast<AEquilNode>(ChildActorComponent->GetChildActor()));
					}
				}
				Current = Cast<AEquilNode>(Current->GetRightChild());
			}
			else
			{
				if (Current->GetLeftChild() == nullptr)
				{
					if (UChildActorComponent* ChildActorComponent = Cast<UChildActorComponent>(AddComponentByClass(UChildActorComponent::StaticClass(), true, FTransform(), false)))
					{
						ChildActorComponent->RegisterComponent();

						ChildActorComponent->SetChildActorClass(SpawnableNodeClass);

						// ChildActorComponent->AttachToComponent(Current->GetPositionLeft(), FAttachmentTransformRules::SnapToTargetIncludingScale);
						// ChildActorComponent->AttachToComponent(SceneComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
						ChildActorComponent->GetChildActor()->AttachToComponent(Current->GetPositionLeft(), FAttachmentTransformRules::SnapToTargetIncludingScale);

						UE_LOG(LogTemp, Warning, TEXT("Added Node For EquilibriumViewInstance"));

						ChildActorComponent->SetRelativeLocation(Current->GetPositionLeft()->GetComponentLocation());
						// ChildActorComponent->SetRelativeRotation(FRotator(0, -90, 0));
						ChildActorComponent->GetChildActor()->SetActorRelativeRotation(FRotator(0, 90, 0));

						AddInstanceComponent(ChildActorComponent);
						Current->SetLeftChild(Cast<AEquilNode>(ChildActorComponent->GetChildActor()));
					}
				}
				Current = Cast<AEquilNode>(Current->GetLeftChild());
			}
		}
		
		if (FChar::ConvertCharDigitToInt(CupCoo[CupCoo.Len() - 1]))
		{
			if (UChildActorComponent* ChildActorComponent = Cast<UChildActorComponent>(AddComponentByClass(UChildActorComponent::StaticClass(), true, FTransform(), false)))
			{
				ChildActorComponent->RegisterComponent();

				ChildActorComponent->SetChildActorClass(SpawnableCupClass);
				
				// ChildActorComponent->AttachToComponent(Current->GetPositionRight(), FAttachmentTransformRules::SnapToTargetIncludingScale);
				// ChildActorComponent->AttachToComponent(SceneComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
				ChildActorComponent->GetChildActor()->AttachToComponent(Current->GetPositionRight(), FAttachmentTransformRules::SnapToTargetIncludingScale);

				UE_LOG(LogTemp, Warning, TEXT("Added Cup For EquilibriumViewInstance"));

				ChildActorComponent->SetRelativeLocation(Current->GetPositionRight()->GetComponentLocation());

				AddInstanceComponent(ChildActorComponent);
				
				if (AEquilCup* Cup = Cast<AEquilCup>(ChildActorComponent->GetChildActor()))
				{
					Current->SetRightChild(Cup);
					Cup->SetCoordinates(FStringToVectorOfInt(CupCoo));
					Cups.Add(Cup);
					// AddCupToArrayOfCups(Cup);
				}
			}
		}
		else
		{
			if (UChildActorComponent* ChildActorComponent = Cast<UChildActorComponent>(AddComponentByClass(UChildActorComponent::StaticClass(), true, FTransform(), false)))
			{
				ChildActorComponent->RegisterComponent();

				ChildActorComponent->SetChildActorClass(SpawnableCupClass);
				
				// ChildActorComponent->AttachToComponent(Current->GetPositionLeft(), FAttachmentTransformRules::SnapToTargetIncludingScale);
				// ChildActorComponent->AttachToComponent(SceneComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
				ChildActorComponent->GetChildActor()->AttachToComponent(Current->GetPositionLeft(), FAttachmentTransformRules::SnapToTargetIncludingScale);

				UE_LOG(LogTemp, Warning, TEXT("Added Cup For EquilibriumViewInstance"));

				ChildActorComponent->SetRelativeLocation(Current->GetPositionLeft()->GetComponentLocation());

				AddInstanceComponent(ChildActorComponent);

				if (AEquilCup* Cup = Cast<AEquilCup>(ChildActorComponent->GetChildActor()))
				{
					Current->SetLeftChild(Cup);
					Cups.Add(Cup);
					Cup->SetCoordinates(FStringToVectorOfInt(CupCoo));
					// AddCupToArrayOfCups(Cup);
				}
			}
		}
	}
	// EquilibriumViewModelComponent->CreateModelInstance(TArrayOfFStringToVectorOfVectorOfInt(CupsCoo));
}

void AEquilibriumView::BeginPlay()
{
	Super::BeginPlay();

	if (EquilibriumViewModelComponent)
	{
		EquilibriumViewModelComponent->CreateModelInstance(TArrayOfFStringToVectorOfVectorOfInt(CupsCoo));
		EquilibriumViewModelComponent->OnChangeStates.AddUObject(this, &AEquilibriumView::CalculateRotation);
	}
	SetCoordinatesForCups();
	
	// CreateEquilibriumByCups();
}

void AEquilibriumView::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEquilibriumView::AddCupToArrayOfCups(AEquilCup* NewCup)
{
	if (NewCup)
	{
		UE_LOG(LogEquilView, Warning, TEXT("Cup Was Added To Array"));
		Cups.Add(NewCup);
	}
}

std::vector<int32_t> AEquilibriumView::FStringToVectorOfInt(const FString& StringToInt) const
{
	std::vector<int32_t> VectorInt;
	
	for (const auto CharToInt : StringToInt)
	{
		VectorInt.push_back(FChar::ConvertCharDigitToInt(CharToInt));
	}
	
	return VectorInt;
}

std::vector<std::vector<int32_t>> AEquilibriumView::TArrayOfFStringToVectorOfVectorOfInt(const TArray<FString>& TArrayToConv) const
{
	std::vector<std::vector<int32_t>> VectorOfVectorOfInt;

	for (auto StringToConv : TArrayToConv)
	{
		VectorOfVectorOfInt.push_back(FStringToVectorOfInt(StringToConv));
	}
	
	return VectorOfVectorOfInt;
}

void AEquilibriumView::SetCoordinatesForCups()
{
	int index = 0;
	for (auto Cup : Cups)
	{
		Cup->SetCoordinates(FStringToVectorOfInt(CupsCoo[index++]));
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
		// Root->CalculateRotation();
		UE_LOG(LogEquilView, Warning, TEXT("View Was Recalculate"));
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
			RootNode->CalculateRotation(FRotator(30.f, 0, 0), FVector(0, 0, -50.f), FVector(0, 0, 50.f));
			break;
		case EquilibriumTypes::NRS_Right:
			RootNode->CalculateRotation(FRotator(-30.f, 0, 0), FVector(0, 0, 50.f), FVector(0, 0, -50.f));
			break;
		case EquilibriumTypes::NRS_Stable:
			RootNode->CalculateRotation(FRotator(0.f, 0, 0), FVector(0, 0, 0), FVector(0, 0, 0));
			break;
		default:
			break;
		}
	}
}
