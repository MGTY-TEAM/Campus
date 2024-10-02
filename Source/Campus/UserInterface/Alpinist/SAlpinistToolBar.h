
#pragma once

#include "CoreMinimal.h"

class UAlpinistIDEController;

class CAMPUS_API SAlpinistToolBar : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SAlpinistToolBar) {}
		SLATE_ARGUMENT(TWeakObjectPtr<UAlpinistIDEController>, AlpinistWidgetOwner)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	virtual bool SupportsKeyboardFocus() const override { return true; }

	TWeakObjectPtr<UAlpinistIDEController> AlpinistWidgetOwner;
private:
	FReply OnToStartPositionButtonClicked() const;
	FReply OnQuitGameButtonClicked() const;

	TSharedPtr<SMenuAnchor> MenuAnchor;
	TSharedRef<SWidget> CreatePopupMenu();
	FReply OnPopupButtonClick();
};
