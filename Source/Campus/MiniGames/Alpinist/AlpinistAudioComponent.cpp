
#include "Campus/MiniGames/Alpinist/AlpinistAudioComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Campus/MiniGames/Alpinist/AlpinistGame.h"

UAlpinistAudioComponent::UAlpinistAudioComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UAlpinistAudioComponent::StartTelegraphSound(const FString& CommandsLine)
{
	StopTelegraphSound();
	
	ListOfCommands = CommandsLine;

	RemoveVoids();
	OnPlayNextCommand();
}

void UAlpinistAudioComponent::StopTelegraphSound()
{
	RepressShoulder();
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(AlpinistCommandSoundTimerHandle);
	}
}

void UAlpinistAudioComponent::RemoveVoids()
{
	ListOfCommands = ListOfCommands.TrimStartAndEnd();

	ListOfCommands.ReplaceInline(TEXT("\r\n"), TEXT(" "));
	ListOfCommands.ReplaceInline(TEXT("\n"), TEXT(" "));
	
	FString ResultString;
	bool bWasLastCharSpace = false;

	for (int32 i = 0; i < ListOfCommands.Len(); i++)
	{
		TCHAR CurrentChar = ListOfCommands[i];

		if (CurrentChar == ' ')
		{
			if (!bWasLastCharSpace)
			{
				ResultString += CurrentChar;
			}
			bWasLastCharSpace = true;
		}
		else
		{
			ResultString += CurrentChar;
			bWasLastCharSpace = false;
		}
	}

	ListOfCommands = ResultString;
}

void UAlpinistAudioComponent::OnPlayNextCommand()
{
	if (!GetWorld()) return;
	
	RepressShoulder();

	if (!ListOfCommands.IsEmpty())
	{
		if (ListOfCommands.Left(1) == TEXT("."))
		{
			if (bLastSymbolPlayed)
			{
				bLastSymbolPlayed = false;
				GetWorld()->GetTimerManager().SetTimer(AlpinistCommandSoundTimerHandle, this, &UAlpinistAudioComponent::OnPlayNextCommand, ShortPauseSoundDuration, false);
				return;
			}

			UGameplayStatics::PlaySound2D(this, TelegraphShortSound);
			PressShoulder();
			bLastSymbolPlayed = true;
			ListOfCommands = ListOfCommands.Mid(1);
			GetWorld()->GetTimerManager().SetTimer(AlpinistCommandSoundTimerHandle, this, &UAlpinistAudioComponent::OnPlayNextCommand, ShortSoundDuration, false);
		}
		else if (ListOfCommands.Left(1) == TEXT("-"))
		{
			if (bLastSymbolPlayed)
			{
				bLastSymbolPlayed = false;
				GetWorld()->GetTimerManager().SetTimer(AlpinistCommandSoundTimerHandle, this, &UAlpinistAudioComponent::OnPlayNextCommand, ShortPauseSoundDuration, false);
				return;
			}

			UGameplayStatics::PlaySound2D(this, TelegraphLongSound);
			PressShoulder();
			bLastSymbolPlayed = true;
			ListOfCommands = ListOfCommands.Mid(1);
			GetWorld()->GetTimerManager().SetTimer(AlpinistCommandSoundTimerHandle, this, &UAlpinistAudioComponent::OnPlayNextCommand, LongSoundDuration, false);
		}
		else
		{
			ListOfCommands = ListOfCommands.Mid(1);
			bLastSymbolPlayed = false;
			GetWorld()->GetTimerManager().SetTimer(AlpinistCommandSoundTimerHandle, this, &UAlpinistAudioComponent::OnPlayNextCommand, LongPauseSoundDuration, false);
		}
	}
}

void UAlpinistAudioComponent::PressShoulder()
{
	if (AAlpinistGame* AlpinistGame = Cast<AAlpinistGame>(GetOwner()))
	{
		AlpinistGame->PressShoulder();
	}
}

void UAlpinistAudioComponent::RepressShoulder()
{
	if (AAlpinistGame* AlpinistGame = Cast<AAlpinistGame>(GetOwner()))
	{
		AlpinistGame->RepressShoulder();
	}
}

