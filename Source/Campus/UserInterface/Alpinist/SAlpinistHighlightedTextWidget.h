#pragma once

#include "CoreMinimal.h"

struct FSlateBrush;
struct FEditableTextBoxStyle;

class UTexture2D;
class FSlateStyleSet;
class SRichTextBlock;
class SHighlightingEditText;
class SMultiLineEditableTextBox;
class UAlpinistIDEController;

class CAMPUS_API SAlpinistHighlightedTextWidget : public SCompoundWidget
{
public:
	SAlpinistHighlightedTextWidget();
	virtual ~SAlpinistHighlightedTextWidget() override;
	SLATE_BEGIN_ARGS(SAlpinistHighlightedTextWidget) {}
		SLATE_ARGUMENT(TWeakObjectPtr<UAlpinistIDEController>, AlpinistWidgetOwner)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	virtual bool SupportsKeyboardFocus() const override { return true; }

	TWeakObjectPtr<UAlpinistIDEController> AlpinistWidgetOwner;
private:
	void OnTextChanged(const FText& NewText);
	FText ApplyHighlighting(const FString& InText);
	FString ReplaceCommand(const FString& SourceText, const FString& CommandToFind, const FString& CommandWithTags);
	TMap<FString, FString> CommandsTags;

	FString PreviousString = "";

	TSharedPtr<SRichTextBlock> RichTextBlock;
	TSharedPtr<SMultiLineEditableTextBox> EditableTextBox;

	FEditableTextBoxStyle* TextBoxStyle;
	FSlateStyleSet* StyleSet;
	UTexture2D* BackTexture;
	FSlateBrush* BackSlateBrush;
};
