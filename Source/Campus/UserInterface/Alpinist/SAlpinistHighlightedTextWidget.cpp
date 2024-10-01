#include "SAlpinistHighlightedTextWidget.h"

#include "Campus/MiniGames/Alpinist/AlpinistIDEController.h"

void SAlpinistHighlightedTextWidget::Construct(const FArguments& InArgs)
{
	bCanSupportFocus = true;
	AlpinistWidgetOwner = InArgs._AlpinistWidgetOwner;

	ChildSlot
	[
		SNew(SImage)
		.ColorAndOpacity(FColor::Red)
	];
}
