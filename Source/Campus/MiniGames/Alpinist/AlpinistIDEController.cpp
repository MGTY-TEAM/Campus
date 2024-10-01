
#include "AlpinistIDEController.h"

#include "GameFramework/HUD.h"
#include "Widgets/SWeakWidget.h"
#include "Campus/MiniGames/Alpinist/AlpinistGame.h"
#include "..\..\UserInterface\Alpinist\SMainAlpinistWidget.h"

UAlpinistIDEController::UAlpinistIDEController()
{
	PrimaryComponentTick.bCanEverTick = false;
	
}

void UAlpinistIDEController::BeginPlay()
{
	Super::BeginPlay();

}

bool UAlpinistIDEController::InitializeAlpinistIDE()
{
	if (GEngine && GEngine->GameViewport)
	{
		AlpinistWidget = SNew(SMainAlpinistWidget).AlpinistWidgetOwner(this);
		GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(AlpinistWidgetContainer, SWeakWidget).PossiblyNullContent(AlpinistWidget.ToSharedRef()));
		
		if (const APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
		{
			if (const AHUD* HUD = PlayerController->GetHUD())
			{
				if (HUD->PlayerOwner)
				{
					HUD->PlayerOwner->bShowMouseCursor = true;
					HUD->PlayerOwner->SetInputMode(FInputModeUIOnly());

					return true;
				}
			}
		}
	}
	
	return false;
}

void UAlpinistIDEController::OnSelectedLevel(int Level)
{
	if (AAlpinistGame* AlpinistGame = Cast<AAlpinistGame>(GetOwner()))
	{
		AlpinistGame->OpenLevel(Level);
	}
}

void UAlpinistIDEController::OnBuildButtonClick()
{
	if (AAlpinistGame* AlpinistGame = Cast<AAlpinistGame>(GetOwner()))
	{
		AlpinistGame->BuildGame();
	}
}

void UAlpinistIDEController::OnRunButtonClick()
{
	if (AAlpinistGame* AlpinistGame = Cast<AAlpinistGame>(GetOwner()))
	{
		AlpinistGame->RunGame();
	}
}

void UAlpinistIDEController::OnToStartPositionButtonClick()
{
	if (AAlpinistGame* AlpinistGame = Cast<AAlpinistGame>(GetOwner()))
	{
		AlpinistGame->ToStartPosition();
	}
}

void UAlpinistIDEController::OnCloseGameButtonClick()
{
	if (GEngine && GEngine->GameViewport && AlpinistWidgetContainer.IsValid())
	{
		GEngine->GameViewport->RemoveViewportWidgetContent(AlpinistWidgetContainer.ToSharedRef());
		
		if (const APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
		{
			if (const AHUD* HUD = PlayerController->GetHUD())
			{
				if (HUD->PlayerOwner)
				{
					HUD->PlayerOwner->bShowMouseCursor = false;
					HUD->PlayerOwner->SetInputMode(FInputModeGameOnly());
				}
			}
		}

		AlpinistWidget.Reset();
		AlpinistWidgetContainer.Reset();
	}
	
	if (AAlpinistGame* AlpinistGame = Cast<AAlpinistGame>(GetOwner()))
	{
		AlpinistGame->CloseGame();
	}
}
