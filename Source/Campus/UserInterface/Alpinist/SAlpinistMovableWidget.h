
#pragma once

#include "CoreMinimal.h"

class CAMPUS_API SAlpinistMovableWidget : public SCompoundWidget
{
public:
	SAlpinistMovableWidget();
	virtual ~SAlpinistMovableWidget() override;
	SLATE_BEGIN_ARGS(SAlpinistMovableWidget) {}
		SLATE_ARGUMENT(TWeakPtr<SWidget>, WidgetOwner)
		SLATE_ARGUMENT(FCurveSequence*, CurveSequence)
	SLATE_END_ARGS()
	
	void Construct(const FArguments& InArgs);
	virtual bool SupportsKeyboardFocus() const override { return true; }

	TWeakPtr<SWidget> WidgetOwner;
	FCurveSequence* CurveSequence;
private:
	FScrollBarStyle ScrollBarStyle;
	TUniquePtr<FSlateStyleSet> StyleSet;
	UTexture2D* BackTexture;
	FSlateBrush* BackSlateBrush;
	FSlateBrush* ContentSlateBrush;

	FReply OnClueClicked();
	bool bIsOpen = false;
};
