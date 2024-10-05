
#pragma once

#include "CoreMinimal.h"

struct FTextBlockStyle;

class SRichTextBlock;
class UAlpinistIDEController;

class CAMPUS_API SAlpinistHighlightedOutputLogWidget : public SCompoundWidget
{
public:
	SAlpinistHighlightedOutputLogWidget();
	SLATE_BEGIN_ARGS(SAlpinistHighlightedOutputLogWidget) {}
		SLATE_ARGUMENT(TWeakObjectPtr<UAlpinistIDEController>, AlpinistWidgetOwner)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	virtual bool SupportsKeyboardFocus() const override { return true; }

	TWeakObjectPtr<UAlpinistIDEController> AlpinistWidgetOwner;
private:
	TSharedPtr<SRichTextBlock> RichTextBlock;
	
	void OnAlpinistLogUpdate(void* InAlpinistLog);
	FSlateStyleSet* StyleSet;
	FTextBlockStyle* DisplayTextBlock;
	FTextBlockStyle* WarningTextBlock;
	FTextBlockStyle* ErrorTextBlock;
	FTextBlockStyle* SuccessTextBlock;
};
