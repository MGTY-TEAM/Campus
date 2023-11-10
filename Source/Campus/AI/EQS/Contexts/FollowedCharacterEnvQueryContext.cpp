// Fill out your copyright notice in the Description page of Project Settings.


#include "Campus/AI/EQS/Contexts/FollowedCharacterEnvQueryContext.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

void UFollowedCharacterEnvQueryContext::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	AActor* const QueryOwner = Cast<AActor>(QueryInstance.Owner.Get());
	UBlackboardComponent* const Blackboard = UAIBlueprintHelperLibrary::GetBlackboard(QueryOwner);
	if (!Blackboard) return;

	AActor* const ContextActor = Cast<AActor>(Blackboard->GetValueAsObject(FollowedCharacterActorKeyName));
	UEnvQueryItemType_Actor::SetContextHelper(ContextData, ContextActor);
}
