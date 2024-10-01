#include "SAlpinistToolBar.h"

#include "Campus/MiniGames/Alpinist/AlpinistIDEController.h"

void SAlpinistToolBar::Construct(const FArguments& InArgs)
{
	bCanSupportFocus = true;
	AlpinistWidgetOwner = InArgs._AlpinistWidgetOwner;

	ChildSlot
	[
		SNew(SImage)
		.ColorAndOpacity(FColor::Blue)
	];
}
