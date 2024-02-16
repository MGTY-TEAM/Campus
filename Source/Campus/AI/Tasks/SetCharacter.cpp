// Fill out your copyright notice in the Description page of Project Settings.

#include "SetCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Campus/Core/CharacterSystem/BaseCharacter.h"
#include "Kismet/GameplayStatics.h"

USetCharacter::USetCharacter()
{
	
}

EBTNodeResult::Type USetCharacter::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComponent  = OwnerComp.GetBlackboardComponent();
	if (BlackboardComponent)
	{
		TArray<AActor*> Pawns;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawn::StaticClass(), Pawns);
		
		for (AActor* Pawn : Pawns)
		{
			if (ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(Pawn))
			{
				BlackboardComponent->SetValueAsObject(CharacterActorKey.SelectedKeyName, BaseCharacter);
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "SetCharacter");
				return EBTNodeResult::Succeeded;
			}
		}
	}

	return EBTNodeResult::Succeeded;
}
