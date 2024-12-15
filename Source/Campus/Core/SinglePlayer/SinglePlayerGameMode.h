// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SinglePlayerGameMode.generated.h"

DECLARE_LOG_CATEGORY_CLASS(LogSinglePlayerGameMode, All, All)

class ABaseCharacter;
class AVRCharacter;

UCLASS()
class CAMPUS_API ASinglePlayerGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	bool value;

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABaseCharacter> PCCharacterClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AVRCharacter> VRCharacterClass;

	virtual void BeginPlay() override;;

};
