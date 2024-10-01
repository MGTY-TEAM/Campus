
#pragma once

#include "CoreMinimal.h"

class UAlpinistIDEController;

class CAMPUS_API SAlpinistIDEWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SAlpinistIDEWidget) {}
		SLATE_ARGUMENT(TWeakObjectPtr<UAlpinistIDEController>, AlpinistWidgetOwner)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	virtual bool SupportsKeyboardFocus() const override { return true; }

	TWeakObjectPtr<UAlpinistIDEController> AlpinistWidgetOwner;
};
