
#pragma once

#include "CoreMinimal.h"

class UAlpinistIDEController;

class CAMPUS_API SMainAlpinistWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SMainAlpinistWidget) {}
		SLATE_ARGUMENT(TWeakObjectPtr<UAlpinistIDEController>, AlpinistWidgetOwner)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime);
	virtual bool SupportsKeyboardFocus() const override { return true; }

	TWeakObjectPtr<UAlpinistIDEController> AlpinistWidgetOwner;

private:
	TSharedPtr<SButton> Button;
	FCurveSequence AnimationSequence;
	FCurveHandle AnimationCurve;
	
	FMargin GetLeftWidgetPadding() const;
	void OnLeftWidgetHovered();
	void OnLeftWidgetUnhovered();
	const float ProtrudingPart = 50.f;
};
