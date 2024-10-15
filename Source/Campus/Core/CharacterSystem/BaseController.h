// BaseController.h

#pragma once
#define BASE_CONTROLLER_DEBUG false

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BaseController.generated.h"

class UInputMappingContext;
// Define a logging category for the BaseController class
DEFINE_LOG_CATEGORY_STATIC(LogBaseController, Log, Log);

class ABaseHUD;
class UInteractionComponent;
class UChatUserComponent;

/**
 * Represents the base controller for the player.
 */
UCLASS()
class CAMPUS_API ABaseController : public APlayerController
{
	GENERATED_BODY()

public:
	ABaseController(); // Default constructor

	protected:
	// Overrides the BeginPlay method of AActor
	virtual void BeginPlay() override;

	// Overrides the SpawnDefaultHUD method of APlayerController
	virtual void SpawnDefaultHUD() override;

	// Overrides the SetupInputComponent method of APlayerController
	virtual void SetupInputComponent() override;

public:
	void SetupPCInputContext();

	void SetupVRInputContext();

private:
	ABaseHUD* M_BaseHUD; // Instance of the base HUD

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UChatUserComponent* M_ChatUserComponent; // Instance of the chat user component

	UPROPERTY(EditDefaultsOnly, Category = "Classes")
	TSubclassOf<ABaseHUD> M_BaseHudClass; // Class of the base HUD

	UPROPERTY(EditDefaultsOnly)
	UInputMappingContext* PCMappingContext;

	UPROPERTY(EditDefaultsOnly)
	UInputMappingContext* VRMappingContext;
};
