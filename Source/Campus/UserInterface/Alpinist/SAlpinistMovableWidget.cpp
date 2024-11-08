#include "SAlpinistMovableWidget.h"

#include "HighlightStyles/AlpinistSlateStyles.h"

SAlpinistMovableWidget::SAlpinistMovableWidget()
{
	BackTexture = UTexture2D::CreateTransient(700, 1000);
	BackSlateBrush = nullptr;
	CurveSequence = nullptr;
}

SAlpinistMovableWidget::~SAlpinistMovableWidget()
{
	FMovableSlateBrush::Delete();
	BackTexture->RemoveFromRoot();
}

void SAlpinistMovableWidget::Construct(const FArguments& InArgs)
{
	bCanSupportFocus = true;
	WidgetOwner = InArgs._WidgetOwner;
	CurveSequence = InArgs._CurveSequence;

	const FSlateFontInfo ButtonTextStyle = FCoreStyle::GetDefaultFontStyle("Regular", 16);
	const FSlateFontInfo RobotoBoldFont = FCoreStyle::GetDefaultFontStyle("Regular", 16);

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
			.ColorAndOpacity(FSlateColor(FLinearColor(220.f, 255.f, 220.f, 1.f)))
			.Image(BackSlateBrush)
		]
		// ----- Movable Widget -----
		+ SOverlay::Slot()
		[
			SNew(SHorizontalBox)
			// ----- Content -----
			+ SHorizontalBox::Slot()
			.FillWidth(15.f)
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
				.WidthOverride(50.f)
				[
					SNew(SButton)
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
					.OnClicked(this, &SAlpinistMovableWidget::OnClueClicked)
					.ButtonColorAndOpacity(FSlateColor(FLinearColor(0.f, 5.f, 10.f, 0.2f)))
					[
						SNew(STextBlock)
						.Text(FText::FromString("?"))
						.Font(RobotoBoldFont)
					]
				]
			]
		]
	];
}

FReply SAlpinistMovableWidget::OnClueClicked()
{
	if (bIsOpen)
	{
		if (CurveSequence)
		{
			UE_LOG(LogTemp, Display, TEXT("Clue Close"));
			CurveSequence->Reverse(); // Воспроизводим анимацию вперёд
		}
		
		bIsOpen = false;
	}
	else
	{
		if (CurveSequence)
		{
			UE_LOG(LogTemp, Display, TEXT("Clue Open"));
			CurveSequence->Play(WidgetOwner.Pin().ToSharedRef()); // Воспроизводим анимацию вперёд
		}
		
		bIsOpen = true;
	}
	
	return FReply::Handled();
}
