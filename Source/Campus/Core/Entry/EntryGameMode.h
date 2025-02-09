// EntryGameMode.h

#pragma once
#define ENTRY_GAME_MODE_DEBUG false

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "EntryGameMode.generated.h"

DEFINE_LOG_CATEGORY_STATIC(LogEntryGameMode, Log, Log);

class UEntryWidget;

/**
 * Represents the game mode for the entry sequence.
 */
UCLASS()
class CAMPUS_API AEntryGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AEntryGameMode(); // Default constructor

	protected:
	// Overrides the BeginPlay method of AGameMode
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "WidgetClasses")
	TSubclassOf<UEntryWidget> M_EntryWidgetClass; // Class of the entry widget
    
	UEntryWidget* M_EntryWidget; // Instance of the entry widget
    
	/**
	 * Handles the execution of the entry widget.
	 *
	 * @param Token The token provided by the entry widget.
	 */
	UFUNCTION()
	void OnEntryWidgetExecute(const FString& Token);
};
