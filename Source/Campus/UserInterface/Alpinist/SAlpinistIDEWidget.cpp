#include "SAlpinistIDEWidget.h"

#include "SAlpinistToolBar.h"
#include "SAlpinistHighlightedTextWidget.h"
#include "HighlightStyles/AlpinistSlateStyles.h"
#include "SAlpinistHighlightedOutputLogWidget.h"
#include "Campus/MiniGames/Alpinist/AlpinistIDEController.h"

SAlpinistIDEWidget::SAlpinistIDEWidget()
{
	BackTexture = UTexture2D::CreateTransient(1000, 1000);
	BackSlateBrush = nullptr;
}

SAlpinistIDEWidget::~SAlpinistIDEWidget()
{
	FMainSlateBrush::Delete();
	BackTexture->RemoveFromRoot();
}

void SAlpinistIDEWidget::Construct(const FArguments& InArgs)
{
	bCanSupportFocus = true;
	AlpinistWidgetOwner = InArgs._AlpinistWidgetOwner;

	const FMargin Padding = FMargin(20.f, 20.f);
	const FMargin ContentPadding = FMargin(20.f, 0.f, 20.f, 0.f);
	const FSlateFontInfo RobotoBoldFont = FCoreStyle::GetDefaultFontStyle("Regular", 16);

	FMainSlateBrush::Initialize(BackTexture);
	BackSlateBrush = &FMainSlateBrush::Get();
	BackTexture->AddToRoot();
	
	ChildSlot
	[
		SNew(SOverlay)
		+ SOverlay::Slot()
		  .HAlign(HAlign_Fill)
		  .VAlign(VAlign_Fill)
		[
			SNew(SImage)
			//.ColorAndOpacity(FColor::Black)
			.Image(BackSlateBrush)
		]
		/*+ SOverlay::Slot()
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
		]*/
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
			  .HAlign(HAlign_Right)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				[
					SNew(SBox)
					.WidthOverride(150)
					[
						SNew(SButton)
						.HAlign(HAlign_Center)
						.VAlign(VAlign_Center)
						.ButtonColorAndOpacity(FSlateColor(FLinearColor(0.f, 6.f, 220.f, 0.27f)))
						.OnClicked(this, &SAlpinistIDEWidget::OnBuildButtonClicked)
						[
							SNew(STextBlock)
							.Text(FText::FromString("Build"))
							.Font(RobotoBoldFont)
						]
					]
				]
				+ SHorizontalBox::Slot()
				[
					SNew(SBox)
					.WidthOverride(100)
					[
						SNew(SButton)
						.HAlign(HAlign_Center)
						.VAlign(VAlign_Center)
						.ButtonColorAndOpacity(FSlateColor(FLinearColor(0.f, 220.f, 6.f, 0.27f)))
						.OnClicked(this, &SAlpinistIDEWidget::OnRunButtonClicked)
						[
							SNew(STextBlock)
							.Text(FText::FromString("Run"))
							.Font(RobotoBoldFont)
						]
					]
				]
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
			  .HAlign(HAlign_Right)
			[
				SNew(SBox)
				.WidthOverride(200)
				[
					SNew(SButton)
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
					.ButtonColorAndOpacity(FSlateColor(FLinearColor(130.f, 130.f, 136.f, 0.27f)))
					.OnClicked(this, &SAlpinistIDEWidget::OnClearLogButtonClicked)
					[
						SNew(STextBlock)
						.Text(FText::FromString("Clear Log"))
						.Font(RobotoBoldFont)
					]
				]
			]
		]
	];
}

FReply SAlpinistIDEWidget::OnBuildButtonClicked() const
{
	if (AlpinistWidgetOwner.IsValid())
	{
		AlpinistWidgetOwner->OnBuildButtonClick();
	}
	
	return FReply::Handled();
}

FReply SAlpinistIDEWidget::OnRunButtonClicked() const
{
	if (AlpinistWidgetOwner.IsValid())
	{
		AlpinistWidgetOwner->OnRunButtonClick();
	}
	
	return FReply::Handled();
}

FReply SAlpinistIDEWidget::OnClearLogButtonClicked() const
{
	if (AlpinistWidgetOwner.IsValid())
	{
		AlpinistWidgetOwner->OnClearLogButtonClick();
	}
	
	return FReply::Handled();
}
