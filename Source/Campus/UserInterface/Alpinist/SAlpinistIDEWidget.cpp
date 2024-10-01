#include "SAlpinistIDEWidget.h"

#include "SAlpinistToolBar.h"
#include "SAlpinistHighlightedTextWidget.h"
#include "SAlpinistHighlightedOutputLogWidget.h"
#include "Campus/MiniGames/Alpinist/AlpinistIDEController.h"

void SAlpinistIDEWidget::Construct(const FArguments& InArgs)
{
	bCanSupportFocus = true;
	AlpinistWidgetOwner = InArgs._AlpinistWidgetOwner;

	const FMargin Padding = FMargin(20.f, 20.f);
	const FMargin ContentPadding = FMargin(20.f, 0.f, 20.f, 0.f);
	const FSlateFontInfo RobotoBoldFont = FCoreStyle::GetDefaultFontStyle("Regular", 16);

	ChildSlot
	[
		SNew(SOverlay)
		+ SOverlay::Slot()
		  .HAlign(HAlign_Fill)
		  .VAlign(VAlign_Fill)
		[
			SNew(SImage)
			.ColorAndOpacity(FColor::Black)
		]
		+ SOverlay::Slot()
		  .HAlign(HAlign_Fill)
		  .VAlign(VAlign_Fill)
		  .Padding(Padding - FMargin(5.f, 5.f))
		[
			SNew(SBorder)
			.BorderBackgroundColor(FLinearColor::White)
			.Padding(FMargin(5.f))
			[
				SNew(SImage)
				.ColorAndOpacity(FColor::Black)
			]
		]
		+ SOverlay::Slot()
		[
			SNew(SVerticalBox)
			// ----- ToolBar -----
			+ SVerticalBox::Slot()
			  .Padding(ContentPadding + FMargin(0.f, 20.f, 0.f, 0.f))
			  .FillHeight(1.0f)
			[
				SNew(SAlpinistToolBar)
				.AlpinistWidgetOwner(InArgs._AlpinistWidgetOwner)
			]
			// ----- HighlightedTextWidget -----
			+ SVerticalBox::Slot()
			  .Padding(ContentPadding)
			  .FillHeight(10.0f)
			[
				SNew(SAlpinistHighlightedTextWidget)
				.AlpinistWidgetOwner(InArgs._AlpinistWidgetOwner)
			]
			// ----- Build and Run Buttons -----
			+ SVerticalBox::Slot()
			  .Padding(ContentPadding)
			  .FillHeight(1.0f)
			[
				SNew(SImage)
				.ColorAndOpacity(FColor::Green)
			]
			// ----- Spacer -----
			+ SVerticalBox::Slot()
			  .Padding(ContentPadding)
			  .FillHeight(1.0f)
			[
				SNew(SSpacer)
			]
			// ----- OutputLog TextBlock -----
			+ SVerticalBox::Slot()
			  .Padding(ContentPadding)
			  .FillHeight(1.0f)
			[
				SNew(SBorder)
				.BorderBackgroundColor(FLinearColor::White)
				.Padding(FMargin(8.f))
				[
					SNew(STextBlock)
					.Text(FText::FromString("OutputLog"))
					.Font(RobotoBoldFont)
				]
			]
			// ----- OutputLog -----
			+ SVerticalBox::Slot()
			  .Padding(ContentPadding)
			  .FillHeight(9.0f)
			[
				SNew(SAlpinistHighlightedOutputLogWidget)
				.AlpinistWidgetOwner(InArgs._AlpinistWidgetOwner)
			]
			// ----- ClearLog Button -----
			+ SVerticalBox::Slot()
			  .Padding(ContentPadding + FMargin(0.f, 0.f, 0.f, 20.f))
			  .FillHeight(1.0f)
			[
				SNew(SImage)
				.ColorAndOpacity(FColor::Emerald)
			]
		]
	];
}
