#include "SAlpinistHighlightedOutputLogWidget.h"

#include "Widgets/Text/SRichTextBlock.h"
#include "Campus/MiniGames/Alpinist/Core/GameController.h"
#include "Campus/MiniGames/Alpinist/AlpinistIDEController.h"

SAlpinistHighlightedOutputLogWidget::SAlpinistHighlightedOutputLogWidget()
{
	TextBlock = new FTextBlockStyle();
	TextBlock->SetFont(FCoreStyle::GetDefaultFontStyle("Regular", 16));
	TextBlock->SetColorAndOpacity(FSlateColor(FLinearColor::Green));
}

void SAlpinistHighlightedOutputLogWidget::Construct(const FArguments& InArgs)
{
	bCanSupportFocus = true;
	AlpinistWidgetOwner = InArgs._AlpinistWidgetOwner;
	if (AlpinistWidgetOwner.IsValid())
	{
		AlpinistWidgetOwner->OnAlpinistLogUpdate.AddRaw(this, &SAlpinistHighlightedOutputLogWidget::OnAlpinistLogUpdate);
	}
	
	ChildSlot
	[
		SNew(SOverlay)
		+ SOverlay::Slot()
		  .HAlign(HAlign_Fill)
		  .VAlign(VAlign_Fill)
		[
			SNew(SBorder)
			.BorderBackgroundColor(FLinearColor::White)
			[
				SNew(SImage)
				.ColorAndOpacity(FColor::Black)
			]
		]
		+ SOverlay::Slot()
		  .HAlign(HAlign_Fill)
		  .VAlign(VAlign_Fill)
		  .Padding(FMargin(7.f))
		[
			SNew(SRichTextBlock)
			.Text(FText::FromString("Log Message..."))
			.TextStyle(TextBlock)
		]
	];
}

void SAlpinistHighlightedOutputLogWidget::OnAlpinistLogUpdate(void* InAlpinistLog)
{
	if (AlpinistGame::AlpinistLog* AlpinistLog = static_cast<AlpinistGame::AlpinistLog*>(InAlpinistLog))
	{
		UE_LOG(LogTemp, Display, TEXT("..., %i"), AlpinistLog->bHasErrors);
	}
}
