#include "SAlpinistMovableWidget.h"

void SAlpinistMovableWidget::Construct(const FArguments& InArgs)
{
	bCanSupportFocus = true;

	ChildSlot
	[
		SNew(SOverlay)
		+ SOverlay::Slot()
		[
			SNew(SImage)
			.ColorAndOpacity(FColor::Cyan)
		]
		+ SOverlay::Slot()
		[
			SNew(STextBlock)
			.Text(FText::FromString("Left Widget -----------------------------------------------------------------"))
		]
	];
}
