#include "SAlpinistMovableWidget.h"

#include "Widgets/Text/SRichTextBlock.h"
#include "HighlightStyles/AlpinistSlateStyles.h"
#include "HighlightStyles/AlpinistTextDecorators.h"
#include "Framework/Text/RichTextLayoutMarshaller.h"
#include "HighlightStyles/FAlpinistMarkupProcessing.h"

SAlpinistMovableWidget::SAlpinistMovableWidget()
{
	StyleSet = MakeUnique<FSlateStyleSet>("MovableWidgetStyleSet");
	BackTexture = UTexture2D::CreateTransient(700, 1000);
	BackSlateBrush = nullptr;
	ContentSlateBrush = nullptr;
	CurveSequence = nullptr;

	ScrollBarStyle = FScrollBarStyle();
	ScrollBarStyle.Thickness = 0.f;
}

SAlpinistMovableWidget::~SAlpinistMovableWidget()
{
	FMainCodeSlateStyleSmall::Delete();
	FSimpleCommandSlateStyleSmall::Delete();
	FConditionCommandSlateStyleSmall::Delete();
	FCheckCommandSlateStyleSmall::Delete();
	FScopeCommandSlateStyleSmall::Delete();
	FNegateCommandSlateStyleSmall::Delete();
	
	FMovableSlateBrush::Delete();
	BackTexture->RemoveFromRoot();
}

void SAlpinistMovableWidget::Construct(const FArguments& InArgs)
{
	bCanSupportFocus = true;
	WidgetOwner = InArgs._WidgetOwner;
	CurveSequence = InArgs._CurveSequence;

	const FMargin TitleContentPadding = FMargin(5.f, 4.f);
	const FMargin ExpandableAreaContentPadding = FMargin(5.f, 0.f, 0.f, 0.f);
	const FMargin BodyContentPadding = FMargin(23.f, 0.f, 4.f, 0.f);
	const FMargin TextContentPadding = FMargin(15.f);

	const FSlateFontInfo ButtonTextStyle = FCoreStyle::GetDefaultFontStyle("Regular", 16);
	const FSlateFontInfo RobotoBoldFont = FCoreStyle::GetDefaultFontStyle("Regular", 16);

	FMovableSlateBrush::Initialize(BackTexture);
	BackSlateBrush = &FMovableSlateBrush::Get();
	BackTexture->AddToRoot();
	
	FMainCodeSlateStyleSmall::Initialize();
	FSimpleCommandSlateStyleSmall::Initialize();
	FConditionCommandSlateStyleSmall::Initialize();
	FCheckCommandSlateStyleSmall::Initialize();
	FScopeCommandSlateStyleSmall::Initialize();
	FNegateCommandSlateStyleSmall::Initialize();

	const FTextBlockStyle* MainTextStyle = &FMainCodeSlateStyleSmall::Get().GetWidgetStyle<FTextBlockStyle>("MainCodeSlateStyleSmall.MainText");
	const FTextBlockStyle* SimpleCommandStyle = &FSimpleCommandSlateStyleSmall::Get().GetWidgetStyle<FTextBlockStyle>("FSimpleCommandSlateStyleSmall.SimpleCommand");
	const FTextBlockStyle* ConditionCommandStyle = &FConditionCommandSlateStyleSmall::Get().GetWidgetStyle<FTextBlockStyle>("FConditionCommandSlateStyleSmall.ConditionCommand");
	const FTextBlockStyle* CheckCommandStyle = &FCheckCommandSlateStyleSmall::Get().GetWidgetStyle<FTextBlockStyle>("FCheckCommandSlateStyleSmall.CheckCommand");
	const FTextBlockStyle* ScopeCommandStyle = &FScopeCommandSlateStyleSmall::Get().GetWidgetStyle<FTextBlockStyle>("FScopeCommandSlateStyleSmall.ScopeCommand");
	const FTextBlockStyle* NegateCommandStyle = &FNegateCommandSlateStyleSmall::Get().GetWidgetStyle<FTextBlockStyle>("FNegateCommandSlateStyleSmall.NegateCommand");

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
		// ----- Background -----
		+ SOverlay::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SNew(SImage)
			.ColorAndOpacity(FSlateColor(FLinearColor(0.7f, 0.7f, 1.f, 1.f)))
			.Image(BackSlateBrush)
		]
		// ----- Movable Widget -----
		+ SOverlay::Slot()
		[
			SNew(SHorizontalBox)
			// ----- Content -----
			+ SHorizontalBox::Slot()
			.FillWidth(15.f)
			[
				SNew(SScrollBox)
				.Orientation(EOrientation::Orient_Vertical)
				.ScrollBarStyle(&ScrollBarStyle)
				.ScrollBarAlwaysVisible(true)
				+ SScrollBox::Slot()
				[
					SNew(SVerticalBox)
					// ------ Об Alpinist Language ------
					+ SVerticalBox::Slot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Top)
					.AutoHeight()
					.Padding(ExpandableAreaContentPadding)
					[
						SNew(SExpandableArea)
						.Padding(BodyContentPadding)
						.InitiallyCollapsed(true)
						.BorderBackgroundColor(FLinearColor::Green)
						.HeaderContent()
						[
							SNew(SOverlay)
							+ SOverlay::Slot()
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Fill)
							[
								SNew(SBorder)
								.BorderBackgroundColor(FLinearColor::Green)
								[
									SNew(SImage)
									.ColorAndOpacity(FSlateColor(FLinearColor(0.f, 0.f, 0.f, 1.f)))
								]
							]
							+ SOverlay::Slot()
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Fill)
							.Padding(TitleContentPadding)
							[
								SNew(STextBlock)
								.Text(FText::FromString(TEXT("Об Alpinist Language"))) // Заголовок панели
								.Font(ButtonTextStyle)
								.Justification(ETextJustify::Center)
							]
						]
						.BodyContent()
						[
							SNew(SBox)
							.WidthOverride(300.f) // Ограничение ширины контейнера
							.HeightOverride(330.f)
							[
								SNew(SOverlay)
								+ SOverlay::Slot()
								.HAlign(HAlign_Fill)
								.VAlign(VAlign_Fill)
								[
									SNew(SImage)
									.ColorAndOpacity(FSlateColor(FLinearColor(0.f, 0.f, 0.f, .6f)))
								]
								+ SOverlay::Slot()
								.HAlign(HAlign_Fill)
								.VAlign(VAlign_Fill)
								[
									SNew(SBorder)
									.BorderBackgroundColor(FLinearColor::Green)
									.Padding(TextContentPadding)
									[
										SNew(SRichTextBlock)
										.Text(FText::FromString(TEXT("\tAlpinist Language - язык программирования, созданный для игры в упрощённой среде, где персонажу необходимо перемещаться и принимать решения в зависимости от окружения. Язык предоставляет собой набор базовых команд, таких как перемещение вперёд, поворот, проверка препятствий, и позволяет использовать логические конструкции для построения более сложных алгоритмов.\n\n\tAlpinist Language позволяет создавать простые алгоритмы для навигации, обучения основам программирования и логического мышления.")))
										.TextStyle(MainTextStyle)
										.Marshaller(FRichTextLayoutMarshaller::Create(FAlpinistMarkupParser::Create(), nullptr, Decorators, StyleSet.Get()))
										.AutoWrapText(true)
										.Clipping(EWidgetClipping::ClipToBounds)
									]
								]
							]
						]
					]
					// ------ Об Alpinist IDE и игре в целом ------
					+ SVerticalBox::Slot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Top)
					.AutoHeight()
					.Padding(ExpandableAreaContentPadding)
					[
						SNew(SExpandableArea)
						.Padding(BodyContentPadding)
						.InitiallyCollapsed(true)
						.BorderBackgroundColor(FLinearColor(0.f, 0.8f, 0.2f, 1.f))
						.HeaderContent()
						[
							SNew(SOverlay)
							+ SOverlay::Slot()
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Fill)
							[
								SNew(SBorder)
								.BorderBackgroundColor(FLinearColor(0.f, 0.3f, 0.7f, 1.f))
								[
									SNew(SImage)
									.ColorAndOpacity(FSlateColor(FLinearColor(0.f, 0.f, 0.f, 1.f)))
								]
							]
							+ SOverlay::Slot()
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Fill)
							.Padding(TitleContentPadding)
							[
								SNew(STextBlock)
								.Text(FText::FromString(TEXT("Об Alpinist IDE и игре в целом"))) // Заголовок панели
								.Font(ButtonTextStyle)
								.Justification(ETextJustify::Center)
							]
						]
						.BodyContent()
						[
							SNew(SBox)
							.WidthOverride(300.f) // Ограничение ширины контейнера
							.HeightOverride(680.f)
							[
								SNew(SOverlay)
								+ SOverlay::Slot()
								.HAlign(HAlign_Fill)
								.VAlign(VAlign_Fill)
								[
									SNew(SImage)
									.ColorAndOpacity(FSlateColor(FLinearColor(0.f, 0.f, 0.f, .6f)))
								]
								+ SOverlay::Slot()
								.HAlign(HAlign_Fill)
								.VAlign(VAlign_Fill)
								[
									SNew(SBorder)
									.BorderBackgroundColor(FLinearColor(0.f, 0.3f, 0.7f, 1.f))
									.Padding(TextContentPadding)
									[
										SNew(SRichTextBlock)
										.Text(FText::FromString(TEXT("\tС помощью кнопки \"Select Level\" вы можете выбрать уровни, которые открываются по ходу их прохождения.\n\n\tС помощью кнопки \"To Start\" вы возвращаете персонажа на его начальное положение. \n\tУчтите! Персонаж изначально смотрит ВВЕРХ.\n\n\tОбласть для написания кода находится под кнопками \"Select Level\", \"To Start\" и \"Quit Game\".\n\n\tС помощью кнопки \"Build\" вы можете проверить корректность написанного вами кода, НЕ запуская движение персонажа.\n\n\tС помощью кнопки \"Run\" изначально так же проверяется корректность написанных команд, а уже после, если код соответствует синтаксису Alpinist Language, запускается.\n\n\tВ блоке Output Log отображается информация о, например, выбранном уровне, ошибках и т.д.\n\tС помощью кнопки \"Clear Log\" можно очистить информацию из этого блока.\n\n\tС помощью кнопки \"Quit Game\" вы можете выйти из игры.")))
										.TextStyle(MainTextStyle)
										.Marshaller(FRichTextLayoutMarshaller::Create(FAlpinistMarkupParser::Create(), nullptr, Decorators, StyleSet.Get()))
										.AutoWrapText(true)
										.Clipping(EWidgetClipping::ClipToBounds)
									]
								]
							]
						]
					]
					// ------ Список команд Alpinist Language ------
					+ SVerticalBox::Slot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Top)
					.AutoHeight()
					.Padding(ExpandableAreaContentPadding)
					[
						SNew(SExpandableArea)
						.Padding(BodyContentPadding)
						.InitiallyCollapsed(true)
						.BorderBackgroundColor(FLinearColor(0.f, 0.7f, 0.7f, 1.f))
						.HeaderContent()
						[
							SNew(SOverlay)
							+ SOverlay::Slot()
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Fill)
							[
								SNew(SBorder)
								.BorderBackgroundColor(FLinearColor(0.f, 0.7f, 0.7f, 1.f))
								[
									SNew(SImage)
									.ColorAndOpacity(FSlateColor(FLinearColor(0.f, 0.f, 0.f, 1.f)))
								]
							]
							+ SOverlay::Slot()
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Fill)
							.Padding(TitleContentPadding)
							[
								SNew(STextBlock)
								.Text(FText::FromString(TEXT("Список команд Alpinist Language"))) // Заголовок панели
								.Font(ButtonTextStyle)
								.Justification(ETextJustify::Center)
							]	
						]
						.BodyContent()
						[
							SNew(SBox)
							.WidthOverride(300.f) // Ограничение ширины контейнера
							.HeightOverride(455.f)
							[
								SNew(SOverlay)
								+ SOverlay::Slot()
								.HAlign(HAlign_Fill)
								.VAlign(VAlign_Fill)
								[
									SNew(SImage)
									.ColorAndOpacity(FSlateColor(FLinearColor(0.f, 0.f, 0.f, .6f)))
								]
								+ SOverlay::Slot()
								.HAlign(HAlign_Fill)
								.VAlign(VAlign_Fill)
								[
									SNew(SBorder)
									.BorderBackgroundColor(FLinearColor(0.f, 0.7f, 0.7f, 1.f))
									.Padding(TextContentPadding)
									[
										SNew(SRichTextBlock)
										.Text(FText::FromString(TEXT("<SimpleCommand>-.-</SimpleCommand> шаг вперёд\n<SimpleCommand>-.</SimpleCommand> поворот налево\n<SimpleCommand>.-</SimpleCommand> поворот направо\n<ConditionCommand>---</ConditionCommand> препятствие спереди\n<ConditionCommand>--.</ConditionCommand> препятствие слева\n<ConditionCommand>.--</ConditionCommand> препятствие справа\n<ConditionCommand>-..-</ConditionCommand> не финиш\n<CheckCommand>.-.</CheckCommand> цикл <CheckCommand>while</CheckCommand>\n<CheckCommand>..</CheckCommand> условие <CheckCommand>if</CheckCommand>\n<CheckCommand>--</CheckCommand> условие <CheckCommand>else</CheckCommand>\n<ScopeCommand>.</ScopeCommand> <ScopeCommand>begin</ScopeCommand> scope\n<ScopeCommand>-</ScopeCommand> <ScopeCommand>end</ScopeCommand> scope\n<NegateCommand>...</NegateCommand> отрицание\n\n\tПримечание: <ConditionCommand>-..-</ConditionCommand> ключевое слово, используемое ТОЛЬКО с циклом <CheckCommand>.-.</CheckCommand> БЕЗ возможности добавить отрицание <NegateCommand>...</NegateCommand>")))
										.TextStyle(MainTextStyle)
										.Marshaller(FRichTextLayoutMarshaller::Create(FAlpinistMarkupParser::Create(), nullptr, Decorators,StyleSet.Get()))
										.AutoWrapText(true)
									]
								]	
							]	
						]
					]
					// ------ Цикл While ------
					+ SVerticalBox::Slot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Top)
					.AutoHeight()
					.Padding(ExpandableAreaContentPadding)
					[
						SNew(SExpandableArea)
						.Padding(BodyContentPadding)
						.InitiallyCollapsed(true)
						.BorderBackgroundColor(FLinearColor(0.f, 0.3f, 0.7f, 1.f))
						.HeaderContent()
						[
							SNew(SOverlay)
							+ SOverlay::Slot()
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Fill)
							[
								SNew(SBorder)
								.BorderBackgroundColor(FLinearColor(0.f, 0.3f, 0.7f, 1.f))
								[
									SNew(SImage)
									.ColorAndOpacity(FSlateColor(FLinearColor(0.f, 0.f, 0.f, 1.f)))
								]
							]
							+ SOverlay::Slot()
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Fill)
							.Padding(TitleContentPadding)
							[
								SNew(STextBlock)
								.Text(FText::FromString(TEXT("Цикл While"))) // Заголовок панели
								.Font(ButtonTextStyle)
								.Justification(ETextJustify::Center)
							]
						]
						.BodyContent()
						[
							SNew(SBox)
							.WidthOverride(300.f) // Ограничение ширины контейнера
							.HeightOverride(430.f)
							[
								SNew(SOverlay)
								+ SOverlay::Slot()
								.HAlign(HAlign_Fill)
								.VAlign(VAlign_Fill)
								[
									SNew(SImage)
									.ColorAndOpacity(FSlateColor(FLinearColor(0.f, 0.f, 0.f, .6f)))
								]
								+ SOverlay::Slot()
								.HAlign(HAlign_Fill)
								.VAlign(VAlign_Fill)
								[
									SNew(SBorder)
									.BorderBackgroundColor(FLinearColor(0.f, 0.3f, 0.7f, 1.f))
									.Padding(TextContentPadding)
									[
										SNew(SRichTextBlock)
										.Text(FText::FromString(TEXT("\tЦикл <CheckCommand>while</CheckCommand> выполняет блок кода пока условие истинно. Он проверяет условие перед каждой итерацией, и если оно верно, код внутри цикла, заключённый между <ScopeCommand>begin</ScopeCommand> и <ScopeCommand>end</ScopeCommand>, выполняется снова и снова. Когда условие становится ложным, цикл останавливается. Пример:\n<CheckCommand>while</CheckCommand> <ConditionCommand>стенка справа</ConditionCommand>\n<ScopeCommand>begin</ScopeCommand>\n\t<SimpleCommand>идти вперёд</SimpleCommand>\n<ScopeCommand>end</ScopeCommand>\n\nНа Alpinist Language данный код выглядит следующим образом:\n<CheckCommand>.-.</CheckCommand> <ConditionCommand>.--</ConditionCommand> <ScopeCommand>.</ScopeCommand> <SimpleCommand>-.-</SimpleCommand> <ScopeCommand>-</ScopeCommand>\n\nТаким образом, в первом и во втором случае мы говорим: пока стенка справа - иди вперёд!")))
										.TextStyle(MainTextStyle)
										.Marshaller(FRichTextLayoutMarshaller::Create(FAlpinistMarkupParser::Create(), nullptr, Decorators, StyleSet.Get()))
										.AutoWrapText(true)
										.Clipping(EWidgetClipping::ClipToBounds)
									]
								]
							]
						]
					]
					// ------ Условия if/else ------
					+ SVerticalBox::Slot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Top)
					.AutoHeight()
					.Padding(ExpandableAreaContentPadding)
					[
						SNew(SExpandableArea)
						.Padding(BodyContentPadding)
						.InitiallyCollapsed(true)
						.BorderBackgroundColor(FLinearColor::Blue)
						.HeaderContent()
						[
							SNew(SOverlay)
							+ SOverlay::Slot()
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Fill)
							[
								SNew(SBorder)
								.BorderBackgroundColor(FLinearColor::Blue)
								[
									SNew(SImage)
									.ColorAndOpacity(FSlateColor(FLinearColor(0.f, 0.f, 0.f, 1.f)))
								]
							]
							+ SOverlay::Slot()
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Fill)
							.Padding(TitleContentPadding)
							[
								SNew(STextBlock)
								.Text(FText::FromString(TEXT("Условия if/else"))) // Заголовок панели
								.Font(ButtonTextStyle)
								.Justification(ETextJustify::Center)
							]
						]
						.BodyContent()
						[
							SNew(SBox)
							.WidthOverride(300.f) // Ограничение ширины контейнера
							.HeightOverride(680.f)
							[
								SNew(SOverlay)
								+ SOverlay::Slot()
								.HAlign(HAlign_Fill)
								.VAlign(VAlign_Fill)
								[
									SNew(SImage)
									.ColorAndOpacity(FSlateColor(FLinearColor(0.f, 0.f, 0.f, .6f)))
								]
								+ SOverlay::Slot()
								.HAlign(HAlign_Fill)
								.VAlign(VAlign_Fill)
								[
									SNew(SBorder)
									.BorderBackgroundColor(FLinearColor::Blue)
									.Padding(TextContentPadding)
									[
										SNew(SRichTextBlock)
										.Text(FText::FromString(TEXT("\tПримечание: необязательно использовать полную конструкцию. Если задача того требует, то можно обойтись использованием единственного <CheckCommand>if</CheckCommand>, убрав часть кода <CheckCommand>else</CheckCommand>.\n\n\tУсловия <CheckCommand>if</CheckCommand>/<CheckCommand>else</CheckCommand> позволяют программе принимать решения: выполняется определенный код, если условие истинно, и другой код, если оно ложно. Для каждого условия блок кода записывается между <ScopeCommand>begin</ScopeCommand> и <ScopeCommand>end</ScopeCommand>. Пример:\n<CheckCommand>if</CheckCommand> <ConditionCommand>стенка спереди</ConditionCommand> \n<ScopeCommand>begin</ScopeCommand> \n\t<SimpleCommand>повернуть налево</SimpleCommand> \n<ScopeCommand>end</ScopeCommand> \n<CheckCommand>else</CheckCommand> \n<ScopeCommand>begin</ScopeCommand> \n\t<SimpleCommand>идти вперёд</SimpleCommand> \n<ScopeCommand>end</ScopeCommand>\n\nНа Alpinist Language данный код выглядит следующим образом:\n<CheckCommand>..</CheckCommand> <ConditionCommand>---</ConditionCommand> <ScopeCommand>.</ScopeCommand> <SimpleCommand>-.</SimpleCommand> <ScopeCommand>-</ScopeCommand> <CheckCommand>--</CheckCommand> <ScopeCommand>.</ScopeCommand> <SimpleCommand>-.-</SimpleCommand> <ScopeCommand>-</ScopeCommand>\n\nТаким образом, в первом и во втором случае мы говорим: если стенка спереди, то поверни налево, иначе иди вперёд!")))
										.TextStyle(MainTextStyle)
										.Marshaller(FRichTextLayoutMarshaller::Create(FAlpinistMarkupParser::Create(), nullptr, Decorators, StyleSet.Get()))
										.AutoWrapText(true)
										.Clipping(EWidgetClipping::ClipToBounds)
									]
								]
							]
						]
					]
					// ------ Отрицание ------
					+ SVerticalBox::Slot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Top)
					.AutoHeight()
					.Padding(ExpandableAreaContentPadding)
					[
						SNew(SExpandableArea)
						.Padding(BodyContentPadding)
						.InitiallyCollapsed(true)
						.BorderBackgroundColor(FLinearColor(0.3f, 0.f, 1.0f, 1.f))
						.HeaderContent()
						[
							SNew(SOverlay)
							+ SOverlay::Slot()
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Fill)
							[
								SNew(SBorder)
								.BorderBackgroundColor(FLinearColor(0.3f, 0.f, 1.0f, 1.f))
								[
									SNew(SImage)
									.ColorAndOpacity(FSlateColor(FLinearColor(0.f, 0.f, 0.f, 1.f)))
								]
							]
							+ SOverlay::Slot()
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Fill)
							.Padding(TitleContentPadding)
							[
								SNew(STextBlock)
								.Text(FText::FromString(TEXT("Отрицание"))) // Заголовок панели
								.Font(ButtonTextStyle)
								.Justification(ETextJustify::Center)
							]
						]
						.BodyContent()
						[
							SNew(SBox)
							.WidthOverride(300.f) // Ограничение ширины контейнера
							.HeightOverride(1100.f)
							[
								SNew(SOverlay)
								+ SOverlay::Slot()
								.HAlign(HAlign_Fill)
								.VAlign(VAlign_Fill)
								[
									SNew(SImage)
									.ColorAndOpacity(FSlateColor(FLinearColor(0.f, 0.f, 0.f, .6f)))
								]
								+ SOverlay::Slot()
								.HAlign(HAlign_Fill)
								.VAlign(VAlign_Fill)
								[
									SNew(SBorder)
									.BorderBackgroundColor(FLinearColor(0.3f, 0.f, 1.0f, 1.f))
									.Padding(TextContentPadding)
									[
										SNew(SRichTextBlock)
										.Text(FText::FromString(TEXT("\tОтрицание может быть добавлено к условиям: <ConditionCommand>---</ConditionCommand>, <ConditionCommand>--.</ConditionCommand> и <ConditionCommand>.--</ConditionCommand> и НЕ может быть добавлено к условию <ConditionCommand>-..-</ConditionCommand>. Первый пример:\n<CheckCommand>if</CheckCommand> <NegateCommand>not</NegateCommand> <ConditionCommand>стенка спереди</ConditionCommand> \n<ScopeCommand>begin</ScopeCommand> \n\t<SimpleCommand>идти вперёд</SimpleCommand> \n<ScopeCommand>end</ScopeCommand>\n\nНа Alpinist Language данный код выглядит следующим образом:\n<CheckCommand>..</CheckCommand> <NegateCommand>...</NegateCommand> <ConditionCommand>---</ConditionCommand> <ScopeCommand>.</ScopeCommand> <SimpleCommand>-.-</SimpleCommand> <ScopeCommand>-</ScopeCommand>\n\nТаким образом, в первом и во втором случае мы говорим: если стенка НЕ спереди - иди вперёд!\n\n\tВторой пример:\n<CheckCommand>while</CheckCommand> <NegateCommand>not</NegateCommand> <ConditionCommand>стенка справа</ConditionCommand>\n<ScopeCommand>begin</ScopeCommand>\n\t<SimpleCommand>идти вперёд</SimpleCommand>\n<ScopeCommand>end</ScopeCommand>\n\nНа Alpinist Language данный код выглядит следующим образом:\n<CheckCommand>.-.</CheckCommand> <NegateCommand>...</NegateCommand> <ConditionCommand>.--</ConditionCommand> <ScopeCommand>.</ScopeCommand> <SimpleCommand>-.-</SimpleCommand> <ScopeCommand>-</ScopeCommand>\n\nТаким образом, в первом и во втором случае мы говорим: пока стенка НЕ справа - иди вперёд!\n\n\tСтоит понимать, что ключевое слово <ConditionCommand>-..-</ConditionCommand> само по себе отрицание, значащее - НЕ финиш. Поэтому НЕ стоит применять отрицание <NegateCommand>...</NegateCommand> к данному ключевому слову. Третий пример:\n<CheckCommand>while</CheckCommand> <ConditionCommand>НЕ финиш</ConditionCommand>\n<ScopeCommand>begin</ScopeCommand>\n\t<SimpleCommand>идти вперёд</SimpleCommand>\n<ScopeCommand>end</ScopeCommand>\n\nНа Alpinist Language данный код выглядит следующим образом:\n<CheckCommand>.-.</CheckCommand> <ConditionCommand>-..-</ConditionCommand> <ScopeCommand>.</ScopeCommand> <SimpleCommand>-.-</SimpleCommand> <ScopeCommand>-</ScopeCommand>\n\nТаким образом, в первом и во втором случае мы говорим: пока НЕ финиш - иди вперёд!")))
										.TextStyle(MainTextStyle)
										.Marshaller(FRichTextLayoutMarshaller::Create(FAlpinistMarkupParser::Create(), nullptr, Decorators, StyleSet.Get()))
										.AutoWrapText(true)
										.Clipping(EWidgetClipping::ClipToBounds)
									]
								]
							]
						]
					]
				]
			]
			// ----- Clue -----
			+ SHorizontalBox::Slot()
			  .VAlign(VAlign_Top)
			  .FillWidth(1.f)
			[
				SNew(SBox)
				.HeightOverride(50.f)
				.WidthOverride(50.f)
				[
					SNew(SButton)
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
					.OnClicked(this, &SAlpinistMovableWidget::OnClueClicked)
					.ButtonColorAndOpacity(FSlateColor(FLinearColor(0.f, 5.f, 10.f, 0.2f)))
					[
						SNew(STextBlock)
						.Text(FText::FromString("?"))
						.Font(RobotoBoldFont)
					]
				]
			]
		]
	];
}

FReply SAlpinistMovableWidget::OnClueClicked()
{
	if (bIsOpen)
	{
		if (CurveSequence)
		{
			UE_LOG(LogTemp, Display, TEXT("Clue Close"));
			CurveSequence->Reverse(); // Воспроизводим анимацию вперёд
		}

		bIsOpen = false;
	}
	else
	{
		if (CurveSequence)
		{
			UE_LOG(LogTemp, Display, TEXT("Clue Open"));
			CurveSequence->Play(WidgetOwner.Pin().ToSharedRef()); // Воспроизводим анимацию вперёд
		}

		bIsOpen = true;
	}

	return FReply::Handled();
}
