
#include "MainAlpinistWidget.h"

void SMainAlpinistWidget::Construct(const FArguments& InArgs)
{
	bCanSupportFocus = true;
	AnimationSequence = FCurveSequence();
	AnimationCurve = AnimationSequence.AddCurve(0.f, 0.3f);

	ChildSlot
	[
		SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.AutoWidth()
		.Padding(TAttribute<FMargin>::Create(TAttribute<FMargin>::FGetter::CreateSP(this, &SMainAlpinistWidget::GetLeftWidgetPadding)))
		//.HAlign(HAlign_Fill)
		//.VAlign(VAlign_Fill)
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
			[
				SNew(SImage)
				.ColorAndOpacity(FColor::Cyan)
			]
			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SButton)
				.OnHovered(this, &SMainAlpinistWidget::OnLeftWidgetHovered) // Наведение на левый виджет
				.OnUnhovered(this, &SMainAlpinistWidget::OnLeftWidgetUnhovered) // Убираем наведение с виджета
				[
					SNew(STextBlock)
					.Text(FText::FromString("Left Widget"))
				]
			]
		]
		+ SHorizontalBox::Slot()
		.FillWidth(1.f)
		//.HAlign(HAlign_Fill)
		//.VAlign(VAlign_Fill)
		[
			SNew(SImage)
			.ColorAndOpacity(FColor::Black)
		]
	];
}

void SMainAlpinistWidget::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	SCompoundWidget::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);
	
	if (AnimationSequence.IsPlaying())
	{
		Invalidate(EInvalidateWidget::Layout); 
	}
}

FMargin SMainAlpinistWidget::GetLeftWidgetPadding() const
{
	return FMargin(CurrentLeftWidgetPadding, 0, 0, 0);
}

void SMainAlpinistWidget::OnLeftWidgetHovered()
{
	if (!AnimationSequence.IsPlaying())
	{
		AnimationSequence.Play(SharedThis(this), true);  // Воспроизводим анимацию вперёд
	}
}

void SMainAlpinistWidget::OnLeftWidgetUnhovered()
{
	if (!AnimationSequence.IsPlaying())
	{
		AnimationSequence.Reverse();  // Воспроизводим анимацию в обратном направлении
	}
}
