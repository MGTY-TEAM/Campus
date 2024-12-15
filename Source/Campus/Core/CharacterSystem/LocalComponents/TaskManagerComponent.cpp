// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskManagerComponent.h"

#include "Campus/Interfaces/MiniGames/MiniGames.h"
#include "Kismet/GameplayStatics.h"


/*UTaskManagerComponent::UTaskManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UTaskManagerComponent::BeginPlay()
{
	Super::BeginPlay();
	MiniGames = TArray<IMiniGames*>();

	UWorld* World = GetWorld();
	if(World)
	{
		TArray<AActor*> Actors;
		UGameplayStatics::GetAllActorsWithInterface(World, UMiniGames::StaticClass(), Actors);

		for(AActor* Actor : Actors)
		{
			if(IMiniGames* MiniGame = Cast<IMiniGames>(Actor))
			{
				MiniGames.Add(MiniGame);
				MiniGame->ExecuteMiniGameCompleted.AddDynamic();
			}
		}
	}
}

void UTaskManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}*/

