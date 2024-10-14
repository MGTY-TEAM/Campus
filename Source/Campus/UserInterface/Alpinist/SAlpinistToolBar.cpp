#include "SAlpinistToolBar.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Campus/MiniGames/Alpinist/AlpinistIDEController.h"
#include "Campus/Libraries/MiniGames/Alpinist/AlpinistGameHelper.h"

void SAlpinistToolBar::Construct(const FArguments& InArgs)
{
	bCanSupportFocus = true;
	AlpinistWidgetOwner = InArgs._AlpinistWidgetOwner;

	const FSlateFontInfo RobotoBoldFont = FCoreStyle::GetDefaultFontStyle("Regular", 8);

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
				.Placement(MenuPlacement_MatchBottomLeft)
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

FReply SAlpinistToolBar::OnLevelSelected(int32 SelectedLevel) const
{
	if (AlpinistWidgetOwner.IsValid())
	{
		AlpinistWidgetOwner->OnSelectedLevel(SelectedLevel);
	}
	
	return FReply::Handled();
}

TSharedRef<SWidget> SAlpinistToolBar::CreatePopupMenu()
{
	const int32 CountOfButtons = UAlpinistGameHelper::DetermineNumberOfLevels(UKismetSystemLibrary::GetProjectDirectory() + "Alpinist/Levels");
	constexpr float ButtonSize = 75.f;
	const FSlateFontInfo ButtonFont = FCoreStyle::GetDefaultFontStyle("Regular", 12);
	const FMargin ButtonPadding = FMargin(5.f);

	TSharedRef<SGridPanel> GridPanel = SNew(SGridPanel);
	
	LevelButtons = TArray<TSharedPtr<SButton>>();
	for (int32 Row = 0; Row < 3; ++Row)
	{
		for (int32 Column = 0; Column < 3; ++Column)
		{
			TSharedPtr<SButton> Button;
			if (Row * 3 + Column < CountOfButtons)  // Проверяем, не вышли ли за пределы нужного количества кнопок
			{
				const int32 ButtonIndex = Row * 3 + Column + 1;
				GridPanel->AddSlot(Column, Row)
				[
					SNew(SBox)
					.HeightOverride(ButtonSize)
					.WidthOverride(ButtonSize)
					.Padding(ButtonPadding)
					[
						SAssignNew(Button, SButton)
						.OnClicked_Lambda([this, ButtonIndex]() -> FReply
						{
							return OnLevelSelected(ButtonIndex);	
						})
						.HAlign(HAlign_Center)  // Горизонтальное выравнивание по центру
						.VAlign(VAlign_Center)
						.IsEnabled(TAttribute<bool>::Create([this, ButtonIndex]() -> bool
						{
							return GetButtonLevelEnable(ButtonIndex);	
						}))
						.ButtonColorAndOpacity(TAttribute<FSlateColor>::Create([this, ButtonIndex]() -> FSlateColor
						{
							return GetButtonLevelSlateColor(ButtonIndex);
						}))
						.Content()
						[
							SNew(STextBlock)
							.Text(FText::FromString(FString::Printf(TEXT("%d"), ButtonIndex)))
							.Justification(ETextJustify::Center)
							.Font(ButtonFont)
						]
					]
				];
				LevelButtons.Add(Button);
			}
		}
	}
	
	return SNew(SOverlay)
	+ SOverlay::Slot()
	[
		SNew(SImage)
		.ColorAndOpacity(FColor::Black)
	]
	+ SOverlay::Slot()
	[
		GridPanel
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
	MenuAnchor->Invalidate(EInvalidateWidgetReason::Visibility);
	
	return FReply::Handled();
}

bool SAlpinistToolBar::GetButtonLevelEnable(int32 ButtonIndex) const
{
	if (AlpinistWidgetOwner.IsValid())
	{
		if (ButtonIndex == AlpinistWidgetOwner->GetSelectedLevel() || AlpinistWidgetOwner->GetPassedLevels().Contains(ButtonIndex)
			|| ButtonIndex == AlpinistWidgetOwner->GetPassedLevels().Num() + 1)
		{
			return true;
		}
	}

	return false;
}

FSlateColor SAlpinistToolBar::GetButtonLevelSlateColor(int32 ButtonIndex) const
{
	if (AlpinistWidgetOwner.IsValid())
	{
		const FSlateColor PassedColor = FSlateColor(FLinearColor(0.f, 6.f, 220.f, 0.27f));
		const FSlateColor NotPassedColor = FSlateColor(FLinearColor(3.f, 3.f, 3.f, 0.27f));
		const FSlateColor SelectedColor = FSlateColor(FLinearColor(0.f, 220.f, 6.f, 0.27f));
		const FSlateColor InactiveColor = FSlateColor(FLinearColor(0.f, 0.f, 0.f, 0.27f));

		if (ButtonIndex == AlpinistWidgetOwner->GetSelectedLevel())
		{
			return SelectedColor;
		}
		if (AlpinistWidgetOwner->GetPassedLevels().Contains(ButtonIndex))
		{
			return PassedColor;
		}
		if (ButtonIndex == AlpinistWidgetOwner->GetPassedLevels().Num() + 1)
		{
			return NotPassedColor;
		}
		
		return InactiveColor;
	}

	return FSlateColor(FLinearColor::Red);
}
