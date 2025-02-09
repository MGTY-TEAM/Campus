// MainMenuGameMode.h

#pragma once
#define MAIN_MENU_GAME_MODE_DEBUG false

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MainMenuGameMode.generated.h"

DEFINE_LOG_CATEGORY_STATIC(LogMainMenuGameMode, Log, Log);

/**
 * Represents the game mode for the main menu.
 */
UCLASS()
class CAMPUS_API AMainMenuGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AMainMenuGameMode(); // Default constructor

	protected:
	// Overrides the BeginPlay method of AGameMode
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> M_MainMenuWidgetClass; // Class of the main menu widget
    
	UUserWidget* M_MainMenuWidget; // Instance of the main menu widget
};