
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AlpinistAudioComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CAMPUS_API UAlpinistAudioComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAlpinistAudioComponent();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sounds")
	USoundWave* TelegraphShortSound = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sounds")
	USoundWave* TelegraphLongSound = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sounds", meta = (ClampMin = "0", ClampMax = "5"))
	float ShortSoundDuration = 0.2f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sounds", meta = (ClampMin = "0", ClampMax = "5"))
	float LongSoundDuration = 0.6f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sounds", meta = (ClampMin = "0", ClampMax = "5"))
	float ShortPauseSoundDuration = 0.2f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sounds", meta = (ClampMin = "0", ClampMax = "5"))
	float LongPauseSoundDuration = 1.2f;

public:	
	void StartTelegraphSound(const FString& CommandsLine);
	void StopTelegraphSound();
private:
	FString ListOfCommands;
	FTimerHandle AlpinistCommandSoundTimerHandle;

	void RemoveVoids();
	void OnPlayNextCommand();

	void PressShoulder();
	void RepressShoulder();

	bool bLastSymbolPlayed = false;
};
