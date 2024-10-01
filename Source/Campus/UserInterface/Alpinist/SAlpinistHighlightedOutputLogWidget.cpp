#include "SAlpinistHighlightedOutputLogWidget.h"

#include "Campus/MiniGames/Alpinist/AlpinistIDEController.h"

void SAlpinistHighlightedOutputLogWidget::Construct(const FArguments& InArgs)
{
	bCanSupportFocus = true;
	AlpinistWidgetOwner = InArgs._AlpinistWidgetOwner;

	ChildSlot
	[
		SNew(SImage)
		.ColorAndOpacity(FColor::Purple)
	];
}
