#include "SMainAlpinistWidget.h"

#include "SAlpinistIDEWidget.h"
#include "SAlpinistMovableWidget.h"
#include "Widgets/Layout/SConstraintCanvas.h"
#include "Campus/MiniGames/Alpinist/AlpinistIDEController.h"

void SMainAlpinistWidget::Construct(const FArguments& InArgs)
{
	bCanSupportFocus = true;
	AlpinistWidgetOwner = InArgs._AlpinistWidgetOwner;

	AnimationSequence = FCurveSequence(0.f, 0.5f);
	AnimationCurve = AnimationSequence.AddCurve(0.f, 0.3f, ECurveEaseFunction::QuadInOut);

	ChildSlot
	[
		SNew(SConstraintCanvas)
		+ SConstraintCanvas::Slot()
		  .Anchors(FAnchors(0, 0, 1, 1))
		  .Offset(FMargin(ProtrudingPart, 0, 0, 0))
		  .Alignment(FVector2D(0.0f, 0.0f))
		[
			SNew(SAlpinistIDEWidget)
			.AlpinistWidgetOwner(InArgs._AlpinistWidgetOwner)
		]
		+ SConstraintCanvas::Slot()
		  .Offset(TAttribute<FMargin>::Create(TAttribute<FMargin>::FGetter::CreateSP(this, &SMainAlpinistWidget::GetLeftWidgetPadding)))
		  .Anchors(FAnchors(0, 0, 0, 1))
		  .AutoSize(true)
		  .Alignment(FVector2D(0.0f, 0.0f))
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
			[
				SNew(SImage)
				.ColorAndOpacity(FColor::Black)
			]
			+ SOverlay::Slot()
			[
				SAssignNew(AlpinistMovableWidget, SAlpinistMovableWidget)
				.WidgetOwner(AsWeak())
				.CurveSequence(&AnimationSequence)
			]
		]
	];
}

void SMainAlpinistWidget::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	SCompoundWidget::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);

	if (AnimationSequence.IsPlaying())
	{
		Invalidate(EInvalidateWidget::Layout); // Обновляем макет виджета при изменении
	}
}

FMargin SMainAlpinistWidget::GetLeftWidgetPadding() const
{
	if (!AlpinistMovableWidget.IsValid()) return FMargin(0.f);
	
	const UE::Slate::FDeprecateVector2DResult ButtonSize = AlpinistMovableWidget.Get()->GetDesiredSize();
	const float ContentWidth = ButtonSize.X;
	const FVector2D ViewportSize = GEngine->GameViewport->Viewport->GetSizeXY();

	if (ViewportSize.X < ContentWidth)
	{
		return FMargin(-ContentWidth + ProtrudingPart, 0, 0, 0); // Левый виджет скрыт за экраном
	}

	// Получаем значение анимации от 0 до 1
	float LerpValue = AnimationCurve.GetLerp();

	// Анимируем от CurrentLeftWidgetPadding до 0 юнитов
	float PaddingValue = FMath::Lerp(-ContentWidth + ProtrudingPart, 0.0f, LerpValue);
	PaddingValue = FMath::Clamp(PaddingValue, -ContentWidth + ProtrudingPart, ViewportSize.X);

	return FMargin(PaddingValue, 0, 0, 0); // Возвращаем отступ
}
