
#pragma once

#include "CoreMinimal.h"

struct FButtonStyle;
class UAlpinistIDEController;

class CAMPUS_API SAlpinistIDEWidget : public SCompoundWidget
{
public:
	SAlpinistIDEWidget();
	~SAlpinistIDEWidget();
	SLATE_BEGIN_ARGS(SAlpinistIDEWidget) {}
		SLATE_ARGUMENT(TWeakObjectPtr<UAlpinistIDEController>, AlpinistWidgetOwner)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	virtual bool SupportsKeyboardFocus() const override { return true; }

	TWeakObjectPtr<UAlpinistIDEController> AlpinistWidgetOwner;
private:
	FReply OnBuildButtonClicked() const;
	FReply OnRunButtonClicked() const;
	FReply OnClearLogButtonClicked() const;

	UTexture2D* BackTexture;
	FSlateBrush* BackSlateBrush;
};
