
#include "AlpinistTextDecorators.h"

#include "Framework/Text/SlateTextRun.h"

FAlpinistCommandDecorator::FAlpinistCommandDecorator(const FTextBlockStyle& InCommandStyle, const FString& InTagName) : CommandStyle(InCommandStyle), TagName(InTagName){}

TSharedRef<ITextDecorator> FAlpinistCommandDecorator::Create(const FTextBlockStyle& InMainCommandStyle, const FString& InTagName)
{
	return MakeShareable(new FAlpinistCommandDecorator(InMainCommandStyle, InTagName));
}

bool FAlpinistCommandDecorator::Supports(const FTextRunParseResults& RunParseResult, const FString& Text) const
{
	return RunParseResult.Name.Equals(TagName, ESearchCase::IgnoreCase);
}

TSharedRef<ISlateRun> FAlpinistCommandDecorator::Create(const TSharedRef<FTextLayout>& TextLayout, const FTextRunParseResults& RunParseResult, const FString& OriginalText, const TSharedRef<FString>& ModelText, const ISlateStyle* Style)
{
	// Инициализируем FRunInfo
	FRunInfo RunInfo(RunParseResult.Name); // Нам нужно получить имя тега
	for (const TPair<FString, FTextRange>& Pair : RunParseResult.MetaData) // Аттрибуты, если есть
	{
		int32 Length = FMath::Max(0, Pair.Value.EndIndex - Pair.Value.BeginIndex);
		RunInfo.MetaData.Add(Pair.Key, OriginalText.Mid(Pair.Value.BeginIndex, Length));
	}
	FTextRange TextRange; // Создаём объект, который будет хранить в сбе диапазон для подсвеченного текста

	const FTextBlockStyle* TextBlockStyle = &CommandStyle; // Берём стиль, которым иницализируем декоратор (он будет использоваться, если в FSlateStyleSet не обнаружится
		// свой стиль для данного декоратора)
	TextRange.BeginIndex = ModelText->Len(); // устанавливаем начальный индекс подстроки
	if (!(RunParseResult.Name.IsEmpty()) && Style->HasWidgetStyle< FTextBlockStyle >(FName(*RunParseResult.Name))) // если мы нашли в FSlateStyleSet стиль для данного декоратора
	{ // то устанавливаем ModelText (текст, который будет рендериться вместо текста с тегами) с диапозоном подстроки ПОД тегами (этот случай избавит нас от тегов)
		*ModelText += OriginalText.Mid(RunParseResult.ContentRange.BeginIndex, RunParseResult.ContentRange.EndIndex - RunParseResult.ContentRange.BeginIndex);
		TextBlockStyle = &(Style->GetWidgetStyle< FTextBlockStyle >(FName(*RunParseResult.Name))); // ну и устанавливаем стиль
	}
	else
	{ // если мы не нашли стиля данному декоратору, то будет использоваться исходный стиль. Диапозон равен всей подстроки с тегами и ModelText будет содержать теги.
		*ModelText += OriginalText.Mid(RunParseResult.OriginalRange.BeginIndex, RunParseResult.OriginalRange.EndIndex - RunParseResult.OriginalRange.BeginIndex);
		CommandStyle.SetColorAndOpacity(FSlateColor(FLinearColor::Yellow)); // устанавливаем сигнализирующий разработчику жёлтый стиль, что что-то пошло не так
	}
	TextRange.EndIndex = ModelText->Len(); // закрываем диапозон длинной ModelText

	// создание FSlateTextRun
	TSharedPtr< FSlateTextRun > SlateTextRun = FSlateTextRun::Create(RunInfo, ModelText, *TextBlockStyle, TextRange);

	if (SlateTextRun)
	{
		SlateTextRun->ApplyFontSizeMultiplierOnTextStyle(1.f);
	}
	
	return SlateTextRun.ToSharedRef();
}
