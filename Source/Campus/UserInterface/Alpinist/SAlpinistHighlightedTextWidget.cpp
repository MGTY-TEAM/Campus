#include "SAlpinistHighlightedTextWidget.h"

#include "SlateExtras.h"
#include "Framework/Text/TextLayout.h"
#include "HighlightStyles/AlpinistSlateStyles.h"
#include "HighlightStyles/AlpinistTextDecorators.h"
#include "Framework/Text/RichTextLayoutMarshaller.h"
#include "HighlightStyles/FAlpinistMarkupProcessing.h"
#include "Campus/MiniGames/Alpinist/AlpinistIDEController.h"

SAlpinistHighlightedTextWidget::SAlpinistHighlightedTextWidget()
{
	TextBoxStyle = new FEditableTextBoxStyle();
	TextBoxStyle->BackgroundColor = FSlateColor(FLinearColor(0.01f, 0.012f, 0.015f, 1.0f));
	
	StyleSet = new FSlateStyleSet("MyStyleSet");
	BackTexture = UTexture2D::CreateTransient(1000, 1000);
	BackSlateBrush = nullptr;
}

SAlpinistHighlightedTextWidget::~SAlpinistHighlightedTextWidget()
{
	FMySlateBrush::Delete();
	FEmptySlateStyle::Delete();
	FMainCodeSlateStyle::Delete();
	FSimpleCommandSlateStyle::Delete();
	FConditionCommandSlateStyle::Delete();
	FCheckCommandSlateStyle::Delete();
	FScopeCommandSlateStyle::Delete();
	FNegateCommandSlateStyle::Delete();
	
	BackTexture->RemoveFromRoot();
}

void SAlpinistHighlightedTextWidget::Construct(const FArguments& InArgs)
{
	bCanSupportFocus = true;
	AlpinistWidgetOwner = InArgs._AlpinistWidgetOwner;
	const FMargin Padding = FMargin(5.f, 5.f);

	FMySlateBrush::Initialize(BackTexture);
	BackSlateBrush = &FMySlateBrush::Get();
	BackTexture->AddToRoot();
	
	FEmptySlateStyle::Initialize();
	FMainCodeSlateStyle::Initialize();
	FSimpleCommandSlateStyle::Initialize();
	FConditionCommandSlateStyle::Initialize();
	FCheckCommandSlateStyle::Initialize();
	FScopeCommandSlateStyle::Initialize();
	FNegateCommandSlateStyle::Initialize();

	const FTextBlockStyle* EmptyStyle = &FEmptySlateStyle::Get().GetWidgetStyle<FTextBlockStyle>("EmptySlateStyle.Empty");
	if (TextBoxStyle) TextBoxStyle->TextStyle = *EmptyStyle;
	
	const FTextBlockStyle* MainTextStyle = &FMainCodeSlateStyle::Get().GetWidgetStyle<FTextBlockStyle>("MainCodeSlateStyle.MainText");
	const FTextBlockStyle* SimpleCommandStyle = &FSimpleCommandSlateStyle::Get().GetWidgetStyle<FTextBlockStyle>("FSimpleCommandSlateStyle.SimpleCommand");
	const FTextBlockStyle* ConditionCommandStyle = &FConditionCommandSlateStyle::Get().GetWidgetStyle<FTextBlockStyle>("FConditionCommandSlateStyle.ConditionCommand");
	const FTextBlockStyle* CheckCommandStyle = &FCheckCommandSlateStyle::Get().GetWidgetStyle<FTextBlockStyle>("FCheckCommandSlateStyle.CheckCommand");
	const FTextBlockStyle* ScopeCommandStyle = &FScopeCommandSlateStyle::Get().GetWidgetStyle<FTextBlockStyle>("FScopeCommandSlateStyle.ScopeCommand");
	const FTextBlockStyle* NegateCommandStyle = &FNegateCommandSlateStyle::Get().GetWidgetStyle<FTextBlockStyle>("FNegateCommandSlateStyle.NegateCommand");
	
	if (StyleSet)
	{
		StyleSet->Set("SimpleCommand", *SimpleCommandStyle);
		StyleSet->Set("ConditionCommand", *ConditionCommandStyle);
		StyleSet->Set("CheckCommand", *CheckCommandStyle);
		StyleSet->Set("ScopeCommand", *ScopeCommandStyle);
		StyleSet->Set("NegateCommand", *NegateCommandStyle);
	}

	TArray<TSharedRef<ITextDecorator>> Decorators;
	Decorators.Add(FAlpinistCommandDecorator::Create(*MainTextStyle, "SimpleCommand"));
	Decorators.Add(FAlpinistCommandDecorator::Create(*MainTextStyle, "ConditionCommand"));
	Decorators.Add(FAlpinistCommandDecorator::Create(*MainTextStyle, "CheckCommand"));
	Decorators.Add(FAlpinistCommandDecorator::Create(*MainTextStyle, "ScopeCommand"));
	Decorators.Add(FAlpinistCommandDecorator::Create(*MainTextStyle, "NegateCommand"));
	
	ChildSlot
	[
		SNew(SOverlay)
		+ SOverlay::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SNew(SBorder)
			.BorderBackgroundColor(FLinearColor::White)
			[
				SNew(SImage)
				.Image(BackSlateBrush)
				//.ColorAndOpacity(FColor::Black)
			]
		]
		+ SOverlay::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(Padding)
		[
			SAssignNew(RichTextBlock, SRichTextBlock)
			.TextStyle(MainTextStyle)
			.Text(ApplyHighlighting(""))
			.Marshaller(FRichTextLayoutMarshaller::Create(FAlpinistMarkupParser::Create(), nullptr, Decorators, StyleSet))
			.AutoWrapText(true)
		]
		+ SOverlay::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(Padding - FMargin(6.f, 2.f))
		[
			SAssignNew(EditableTextBox, SMultiLineEditableTextBox)
			.OnTextChanged(this, &SAlpinistHighlightedTextWidget::OnTextChanged)
			.Text(FText::FromString(""))
			.Style(TextBoxStyle)
			.BackgroundColor(FLinearColor::Transparent)
			.AutoWrapText(true)
		]
	];
}

void SAlpinistHighlightedTextWidget::OnTextChanged(const FText& NewText)
{
	if (RichTextBlock.IsValid())
	{
		RichTextBlock->SetText(ApplyHighlighting(NewText.ToString()));
		// UE_LOG(LogTemp, Warning, TEXT("TEXT: %s"), *RichTextBlock->GetText().ToString());
		
		if (EditableTextBox.IsValid())
		{
			UE_LOG(LogTemp, Warning, TEXT("TEXT: %s"), *EditableTextBox->GetText().ToString());
			if (AlpinistWidgetOwner.IsValid())
			{
				AlpinistWidgetOwner->OnChangeCode(*EditableTextBox->GetText().ToString());
			}
		}
	}
}

FText SAlpinistHighlightedTextWidget::ApplyHighlighting(const FString& InText)
{
	FString UpdatedText = InText;

	// TODO: Написать код для добавления тегов
	
	const FString KeywordMove = TEXT("-.-");
	UpdatedText = ReplaceCommand(UpdatedText, KeywordMove, FString::Printf(TEXT("<SimpleCommand>%s</SimpleCommand>"), *KeywordMove));
	// UpdatedText = UpdatedText.Replace(*Keyword, *FString::Printf(TEXT("<SimpleCommand>%s</SimpleCommand>"), *Keyword));
	const FString KeywordLeft = TEXT("-.");
	UpdatedText = ReplaceCommand(UpdatedText, KeywordLeft, FString::Printf(TEXT("<SimpleCommand>%s</SimpleCommand>"), *KeywordLeft));
	const FString KeywordRight = TEXT(".-");
	UpdatedText = ReplaceCommand(UpdatedText, KeywordRight, FString::Printf(TEXT("<SimpleCommand>%s</SimpleCommand>"), *KeywordRight));
	
	const FString KeywordWallAhead = TEXT("---");
	UpdatedText = ReplaceCommand(UpdatedText, KeywordWallAhead, FString::Printf(TEXT("<ConditionCommand>%s</ConditionCommand>"), *KeywordWallAhead));
	// UpdatedText = UpdatedText.Replace(*Keyword2, *FString::Printf(TEXT("<ConditionCommand>%s</ConditionCommand>"), *Keyword2));
	const FString KeywordWallLeft = TEXT("--.");
	UpdatedText = ReplaceCommand(UpdatedText, KeywordWallLeft, FString::Printf(TEXT("<ConditionCommand>%s</ConditionCommand>"), *KeywordWallLeft));
	const FString KeywordWallRight = TEXT(".--");
	UpdatedText = ReplaceCommand(UpdatedText, KeywordWallRight, FString::Printf(TEXT("<ConditionCommand>%s</ConditionCommand>"), *KeywordWallRight));
	const FString KeywordNotEnd = TEXT("-..-");
	UpdatedText = ReplaceCommand(UpdatedText, KeywordNotEnd, FString::Printf(TEXT("<ConditionCommand>%s</ConditionCommand>"), *KeywordNotEnd));

	const FString KeywordWhile = TEXT(".-.");
	UpdatedText = ReplaceCommand(UpdatedText, KeywordWhile, FString::Printf(TEXT("<CheckCommand>%s</CheckCommand>"), *KeywordWhile));

	const FString KeywordIf = TEXT("..");
	UpdatedText = ReplaceCommand(UpdatedText, KeywordIf, FString::Printf(TEXT("<CheckCommand>%s</CheckCommand>"), *KeywordIf));
	const FString KeywordElse = TEXT("--");
	UpdatedText = ReplaceCommand(UpdatedText, KeywordElse, FString::Printf(TEXT("<CheckCommand>%s</CheckCommand>"), *KeywordElse));

	const FString KeywordBegin = TEXT(".");
	UpdatedText = ReplaceCommand(UpdatedText, KeywordBegin, FString::Printf(TEXT("<ScopeCommand>%s</ScopeCommand>"), *KeywordBegin));
	const FString KeywordEnd = TEXT("-");
	UpdatedText = ReplaceCommand(UpdatedText, KeywordEnd, FString::Printf(TEXT("<ScopeCommand>%s</ScopeCommand>"), *KeywordEnd));
	const FString KeywordNegate = TEXT("...");
	UpdatedText = ReplaceCommand(UpdatedText, KeywordNegate, FString::Printf(TEXT("<NegateCommand>%s</NegateCommand>"), *KeywordNegate));
	
	return FText::FromString(UpdatedText);
}

FString SAlpinistHighlightedTextWidget::ReplaceCommand(const FString& SourceText, const FString& CommandToFind, const FString& CommandWithTags)
{
	FString ResultString = FString();

	const int32 SubstringLength = CommandToFind.Len();
	int32 StartIndex = 0;
	while (StartIndex < SourceText.Len())
	{
		const int32 FoundIndex = SourceText.Find(CommandToFind, ESearchCase::IgnoreCase, ESearchDir::FromStart, StartIndex);
		if (FoundIndex == INDEX_NONE)
		{
			ResultString.Append(SourceText.Mid(StartIndex));
			break;
		}

		const bool bIsStartOfWord = (FoundIndex == 0) || (SourceText[FoundIndex - 1] == ' ') || (SourceText[FoundIndex - 1] == '\n') || (SourceText[FoundIndex - 1] == '\r');
		const bool bIsEndOfWord = (FoundIndex + SubstringLength == SourceText.Len()) || (SourceText[FoundIndex + SubstringLength] == ' ')
									|| (SourceText[FoundIndex + SubstringLength] == '\n') || (SourceText[FoundIndex + SubstringLength] == '\r');
		if (bIsStartOfWord && bIsEndOfWord)
		{
			ResultString.Append(SourceText.Mid(StartIndex, FoundIndex - StartIndex));
			ResultString.Append(CommandWithTags);
		}
		else
		{
			ResultString.Append(SourceText.Mid(StartIndex, FoundIndex + SubstringLength - StartIndex));
		}
		StartIndex = FoundIndex + SubstringLength;
	}

	return ResultString;
}
