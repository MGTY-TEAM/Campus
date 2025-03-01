#include "SAlpinistHighlightedOutputLogWidget.h"

#include "Widgets/Text/SRichTextBlock.h"
#include "HighlightStyles/AlpinistTextDecorators.h"
#include "Framework/Text/RichTextLayoutMarshaller.h"
#include "Campus/MiniGames/Alpinist/Core/GameController.h"
#include "Campus/MiniGames/Alpinist/AlpinistIDEController.h"
#include "Framework/Text/RichTextMarkupProcessing.h"

SAlpinistHighlightedOutputLogWidget::SAlpinistHighlightedOutputLogWidget()
{
	StyleSet = MakeUnique<FSlateStyleSet>("OutputLogStyleSet");

	DisplayTextBlock = MakeUnique<FTextBlockStyle>();
	DisplayTextBlock->SetFont(FCoreStyle::GetDefaultFontStyle("Regular", 12));
	DisplayTextBlock->SetColorAndOpacity(FSlateColor(FLinearColor::White));

	WarningTextBlock = MakeUnique<FTextBlockStyle>();
	WarningTextBlock->SetFont(FCoreStyle::GetDefaultFontStyle("Regular", 12));
	WarningTextBlock->SetColorAndOpacity(FSlateColor(FLinearColor::Yellow));

	ErrorTextBlock = MakeUnique<FTextBlockStyle>();
	ErrorTextBlock->SetFont(FCoreStyle::GetDefaultFontStyle("Regular", 12));
	ErrorTextBlock->SetColorAndOpacity(FSlateColor(FLinearColor::Red));
	
	SuccessTextBlock = MakeUnique<FTextBlockStyle>();
	SuccessTextBlock->SetFont(FCoreStyle::GetDefaultFontStyle("Regular", 12));
	SuccessTextBlock->SetColorAndOpacity(FSlateColor(FLinearColor::Green));
}

void SAlpinistHighlightedOutputLogWidget::Construct(const FArguments& InArgs)
{
	bCanSupportFocus = true;
	AlpinistWidgetOwner = InArgs._AlpinistWidgetOwner;
	if (AlpinistWidgetOwner.IsValid())
	{
		AlpinistWidgetOwner->OnAlpinistLogUpdate.AddRaw(this, &SAlpinistHighlightedOutputLogWidget::OnAlpinistLogUpdate);
	}
	
	if (StyleSet)
	{
		StyleSet->Set("DisplayText", *DisplayTextBlock);
		StyleSet->Set("WarningText", *WarningTextBlock);
		StyleSet->Set("ErrorText", *ErrorTextBlock);
		StyleSet->Set("SuccessText", *SuccessTextBlock);
	}
	TArray<TSharedRef<ITextDecorator>> Decorators;
	Decorators.Add(FAlpinistCommandDecorator::Create(*DisplayTextBlock, "DisplayText"));
	Decorators.Add(FAlpinistCommandDecorator::Create(*DisplayTextBlock, "WarningText"));
	Decorators.Add(FAlpinistCommandDecorator::Create(*DisplayTextBlock, "ErrorText"));
	Decorators.Add(FAlpinistCommandDecorator::Create(*DisplayTextBlock, "SuccessText"));
	
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
				.ColorAndOpacity(FColor::Black)
			]
		]
		+ SOverlay::Slot()
		  .HAlign(HAlign_Fill)
		  .VAlign(VAlign_Fill)
		  .Padding(FMargin(7.f))
		[
			SNew(SScrollBox)
			+ SScrollBox::Slot()
			[
				SAssignNew(RichTextBlock, SRichTextBlock)
				.Text(FText::FromString("<SuccessText>Log Message...</>"))
				.TextStyle(DisplayTextBlock.Get())
				.Marshaller(FRichTextLayoutMarshaller::Create(FDefaultRichTextMarkupParser::Create(), nullptr, Decorators, StyleSet.Get()))
			]
		]
	];
}

void SAlpinistHighlightedOutputLogWidget::OnAlpinistLogUpdate(void* InAlpinistLog)
{
	if (AlpinistGame::AlpinistLog* AlpinistLog = static_cast<AlpinistGame::AlpinistLog*>(InAlpinistLog))
	{
		FString OutputLogInformation = FString();
		
		for (AlpinistGame::MessageLog messageLog : *AlpinistLog->GetListOfLog())
		{
			if (messageLog.Type == AlpinistGame::DisplayMes)
			{
				OutputLogInformation.Append(FString("<DisplayText>") + FString(messageLog.Message.c_str()) + FString("</>") + "\n");
			}
			else if (messageLog.Type == AlpinistGame::WarningMes)
			{
				OutputLogInformation.Append(FString("<WarningText>") + FString(messageLog.Message.c_str()) + FString("</>") + "\n");
			}
			else if (messageLog.Type == AlpinistGame::ErrorMes)
			{
				OutputLogInformation.Append(FString("<ErrorText>") + FString(messageLog.Message.c_str()) + FString("</>") + "\n");
			}
			else if (messageLog.Type == AlpinistGame::SuccessMes)
			{
				OutputLogInformation.Append(FString("<SuccessText>") + FString(messageLog.Message.c_str()) + FString("</>") + "\n");
			}
			// OutputLogInformation.Append(FString(messageLog.Message.c_str()) + "\n");
			UE_LOG(LogTemp, Display, TEXT("%s"), *FString(messageLog.Message.c_str()));
		}

		if (RichTextBlock.IsValid())
		{
			RichTextBlock->SetText(FText::FromString(OutputLogInformation));
		}
	}
}
