
#pragma once

#include "CoreMinimal.h"

class CAMPUS_API SAlpinistMovableWidget : public SCompoundWidget
{
public:
	SAlpinistMovableWidget();
	virtual ~SAlpinistMovableWidget() override;
	SLATE_BEGIN_ARGS(SAlpinistMovableWidget) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	virtual bool SupportsKeyboardFocus() const override { return true; }
private:
	UTexture2D* BackTexture;
	FSlateBrush* BackSlateBrush;
};