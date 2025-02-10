
#pragma once

#include "CoreMinimal.h"
#include "Framework/Text/ITextDecorator.h"

class CAMPUS_API FAlpinistCommandDecorator : public ITextDecorator
{
public:
	static TSharedRef<ITextDecorator> Create(const FTextBlockStyle& InMainCommandStyle, const FString& InTagName);

	virtual bool Supports(const FTextRunParseResults& RunParseResult, const FString& Text) const override;
	virtual TSharedRef<ISlateRun> Create(const TSharedRef<FTextLayout>& TextLayout, const FTextRunParseResults& RunParseResult, const FString& OriginalText, const TSharedRef<FString>& ModelText, const ISlateStyle* Style) override;
private:
	FAlpinistCommandDecorator(const FTextBlockStyle& InCommandStyle, const FString& InTagName);
	FTextBlockStyle CommandStyle;
	FString TagName;
};