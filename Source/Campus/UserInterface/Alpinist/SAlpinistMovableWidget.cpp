#include "SAlpinistMovableWidget.h"

#include "HighlightStyles/AlpinistSlateStyles.h"

SAlpinistMovableWidget::SAlpinistMovableWidget()
{
	BackTexture = UTexture2D::CreateTransient(700, 1000);
	BackSlateBrush = nullptr;
}

SAlpinistMovableWidget::~SAlpinistMovableWidget()
{
	FMovableSlateBrush::Delete();
	BackTexture->RemoveFromRoot();
}

void SAlpinistMovableWidget::Construct(const FArguments& InArgs)
{
	bCanSupportFocus = true;

	const FSlateFontInfo ButtonTextStyle = FCoreStyle::GetDefaultFontStyle("Regular", 16);

	FMovableSlateBrush::Initialize(BackTexture);
	BackSlateBrush = &FMovableSlateBrush::Get();
	BackTexture->AddToRoot();

	ChildSlot
	[
		SNew(SOverlay)
		// ----- Background -----
		+ SOverlay::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SNew(SImage)
			.ColorAndOpacity(FSlateColor(FLinearColor(0.f, 255.f, 200.f, 1.f)))
			.Image(BackSlateBrush)
		]
		// ----- Movable Widget -----
		+ SOverlay::Slot()
		[
			SNew(SHorizontalBox)
			// ----- Content -----
			+ SHorizontalBox::Slot()
			.FillWidth(9.f)
			[
				// SNew(STextBlock)
				// .Text(FText::FromString("Left Widget -----------------------------------------------------------------"))
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					SNew(SExpandableArea)
					.InitiallyCollapsed(true)
					.HeaderContent()
					[
						SNew(STextBlock)
						.Text(FText::FromString("About Alpinist Language"))  // Заголовок панели
						.Font(ButtonTextStyle)
						.Justification(ETextJustify::Center)
					]
					.BodyContent()
					[
						SNew(SImage)
						.ColorAndOpacity(FColor::Red)
					]
				]
			]
			// ----- Clue -----
			+ SHorizontalBox::Slot()
			.VAlign(VAlign_Top)
			.FillWidth(1.f)
			[
				SNew(SBox)
				.HeightOverride(50.f)
				[
					SNew(SImage)
					.ColorAndOpacity(FColor::Red)
				]
			]
		]
	];
}
