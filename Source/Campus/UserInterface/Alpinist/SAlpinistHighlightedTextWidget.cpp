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

	const FTextBlockStyle* EmptyStyle = &FEmptySlateStyle::Get().GetWidgetStyle<FTextBlockStyle>("EmptySlateStyle.Empty");
	if (TextBoxStyle) TextBoxStyle->TextStyle = *EmptyStyle;
	
	const FTextBlockStyle* MainTextStyle = &FMainCodeSlateStyle::Get().GetWidgetStyle<FTextBlockStyle>("MainCodeSlateStyle.MainText");
	const FTextBlockStyle* SimpleCommandStyle = &FSimpleCommandSlateStyle::Get().GetWidgetStyle<FTextBlockStyle>("FSimpleCommandSlateStyle.SimpleCommand");
	const FTextBlockStyle* ConditionCommandStyle = &FConditionCommandSlateStyle::Get().GetWidgetStyle<FTextBlockStyle>("FConditionCommandSlateStyle.ConditionCommand");

	if (StyleSet)
	{
		StyleSet->Set("SimpleCommand", *SimpleCommandStyle);
		StyleSet->Set("ConditionCommand", *ConditionCommandStyle);
	}

	TArray<TSharedRef<ITextDecorator>> Decorators;
	Decorators.Add(FAlpinistCommandDecorator::Create(*MainTextStyle, "SimpleCommand"));
	Decorators.Add(FAlpinistCommandDecorator::Create(*MainTextStyle, "ConditionCommand"));
	
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
		.Padding(Padding - FMargin(6.f, 1.f))
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
	
	const FString Keyword = TEXT("-.-");
	UpdatedText = UpdatedText.Replace(*Keyword, *FString::Printf(TEXT("<SimpleCommand>%s</SimpleCommand>"), *Keyword));
	const FString Keyword2 = TEXT("---");
	UpdatedText = UpdatedText.Replace(*Keyword2, *FString::Printf(TEXT("<ConditionCommand>%s</ConditionCommand>"), *Keyword2));
	
	return FText::FromString(UpdatedText);
}
