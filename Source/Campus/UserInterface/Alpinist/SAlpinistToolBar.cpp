#include "SAlpinistToolBar.h"

#include "Campus/MiniGames/Alpinist/AlpinistIDEController.h"

void SAlpinistToolBar::Construct(const FArguments& InArgs)
{
	bCanSupportFocus = true;
	AlpinistWidgetOwner = InArgs._AlpinistWidgetOwner;

	const FSlateFontInfo RobotoBoldFont = FCoreStyle::GetDefaultFontStyle("Regular", 16);

	ChildSlot
	[
		SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.HAlign(HAlign_Left)
		.FillWidth(1.f)
		[
			SNew(SHorizontalBox)
			// ----- Select Level Button -----
			+ SHorizontalBox::Slot()
			[
				SAssignNew(MenuAnchor, SMenuAnchor)
				.Placement(MenuPlacement_ComboBox)
				.OnGetMenuContent(this, &SAlpinistToolBar::CreatePopupMenu)
				[
					SNew(SBox)
					.WidthOverride(200)
					[
						SNew(SButton)
						.HAlign(HAlign_Center)
						.VAlign(VAlign_Center)
						.ButtonColorAndOpacity(FSlateColor(FLinearColor(3.f, 3.f, 3.f, 0.1f)))
						.OnClicked(this, &SAlpinistToolBar::OnPopupButtonClick)
						[
							SNew(STextBlock)
							.Text(FText::FromString("Select Level"))
							.Font(RobotoBoldFont)
						]
					]
				]
			]
			// ----- To Start Position Button -----
			+ SHorizontalBox::Slot()
			[
				SNew(SBox)
				.WidthOverride(200)
				[
					SNew(SButton)
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
					.ButtonColorAndOpacity(FSlateColor(FLinearColor(3.f, 3.f, 3.f, 0.1f)))
					.OnClicked(this, &SAlpinistToolBar::OnToStartPositionButtonClicked)
					[
						SNew(STextBlock)
						.Text(FText::FromString("To Start"))
						.Font(RobotoBoldFont)
					]
				]
			]
		]
		+ SHorizontalBox::Slot()
		.FillWidth(2.f)
		[
			SNullWidget::NullWidget
		]
		// ----- Quit Game Button -----
		+ SHorizontalBox::Slot()
		.HAlign(HAlign_Right)
		.FillWidth(1.f)
		[
			SNew(SBox)
			.WidthOverride(200)
			[
				SNew(SButton)
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
				.ButtonColorAndOpacity(FSlateColor(FLinearColor(3.f, 3.f, 3.f, 0.1f)))
				.OnClicked(this, &SAlpinistToolBar::OnQuitGameButtonClicked)
				[
					SNew(STextBlock)
					.Text(FText::FromString("Quit Game"))
					.Font(RobotoBoldFont)
				]
			]
		]
	];
}

FReply SAlpinistToolBar::OnToStartPositionButtonClicked() const
{
	if (AlpinistWidgetOwner.IsValid())
	{
		AlpinistWidgetOwner->OnToStartPositionButtonClick();
	}

	return FReply::Handled();
}

FReply SAlpinistToolBar::OnQuitGameButtonClicked() const
{
	if (AlpinistWidgetOwner.IsValid())
	{
		AlpinistWidgetOwner->OnQuitGameButtonClick();
	}

	return FReply::Handled();
}

TSharedRef<SWidget> SAlpinistToolBar::CreatePopupMenu()
{
	return SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.Padding(10)
		[
			SNew(STextBlock).Text(FText::FromString("Option 1"))
		]
		+ SVerticalBox::Slot()
		.Padding(10)
		[
			SNew(STextBlock).Text(FText::FromString("Option 2"))
		]
		+ SVerticalBox::Slot()
		.Padding(10)
		[
			SNew(STextBlock).Text(FText::FromString("Option 3"))
		];
}

FReply SAlpinistToolBar::OnPopupButtonClick()
{
	if (MenuAnchor->IsOpen())
	{
		MenuAnchor->SetIsOpen(false); // Закрываем меню, если оно уже открыто
	}
	else
	{
		MenuAnchor->SetIsOpen(true); // Открываем меню, если оно закрыто
	}
	
	return FReply::Handled();
}
