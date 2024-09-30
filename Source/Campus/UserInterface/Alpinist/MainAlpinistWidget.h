
#pragma once

#include "CoreMinimal.h"

class UAlpinistIDEController;

class SMainAlpinistWidget : public SCompoundWidget
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
	FCurveSequence AnimationSequence;
	FCurveHandle AnimationCurve;
	float CurrentLeftWidgetPadding = -75.f;
	
	FMargin GetLeftWidgetPadding() const;
	void OnLeftWidgetHovered();
	void OnLeftWidgetUnhovered();
};
