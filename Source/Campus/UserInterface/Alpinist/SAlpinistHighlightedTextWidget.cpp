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

	CommandsTags = TMap<FString, FString>();
	CommandsTags.Add(TEXT("-.-"), TEXT("<SimpleCommand>-.-</SimpleCommand>"));
	CommandsTags.Add(TEXT("-."), TEXT("<SimpleCommand>-.</SimpleCommand>"));
	CommandsTags.Add(TEXT(".-"), TEXT("<SimpleCommand>.-</SimpleCommand>"));
	CommandsTags.Add(TEXT("---"), TEXT("<ConditionCommand>---</ConditionCommand>"));
	CommandsTags.Add(TEXT("--."), TEXT("<ConditionCommand>--.</ConditionCommand>"));
	CommandsTags.Add(TEXT(".--"), TEXT("<ConditionCommand>.--</ConditionCommand>"));
	CommandsTags.Add(TEXT("-..-"), TEXT("<ConditionCommand>-..-</ConditionCommand>"));
	CommandsTags.Add(TEXT(".-."), TEXT("<CheckCommand>.-.</CheckCommand>"));
	CommandsTags.Add(TEXT(".."), TEXT("<CheckCommand>..</CheckCommand>"));
	CommandsTags.Add(TEXT("--"), TEXT("<CheckCommand>--</CheckCommand>"));
	CommandsTags.Add(TEXT("."), TEXT("<ScopeCommand>.</ScopeCommand>"));
	CommandsTags.Add(TEXT("-"), TEXT("<ScopeCommand>-</ScopeCommand>"));
	CommandsTags.Add(TEXT("..."), TEXT("<NegateCommand>...</NegateCommand>"));
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

	// Цвета выбирала Екатерина Кузнецова Павловна, 14 февраля 2005 г. рождения. P.S. 
	// Эти цвета посвященны пауку, которого мы убивали ночью у меня дома и нечаянно оторвали ему лапу, и он убежал от нас.
	// Это послание его детям, потому что мы были злые и лишили детей отца.
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
			// UE_LOG(LogTemp, Warning, TEXT("TEXT: %s"), *EditableTextBox->GetText().ToString());
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

	FString ResultString = FString();
	FString CommandString = FString();
	int32 NumOfChar = 0;
	for (const TCHAR& Char : UpdatedText.GetCharArray())
	{
		++NumOfChar;
		if (Char == ' ' || Char == '\n' || Char == '\r' || NumOfChar == UpdatedText.GetCharArray().Num())
		{
			if (!CommandString.IsEmpty())
			{
				if (CommandsTags.Contains(CommandString))
				{
					CommandString = FString(*CommandsTags.Find(CommandString));
				}
			}

			ResultString.Append(CommandString);
			ResultString.AppendChar(Char);
			CommandString.Empty();
			continue;
		}
		CommandString.AppendChar(Char);
	}

	return FText::FromString(ResultString);
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
