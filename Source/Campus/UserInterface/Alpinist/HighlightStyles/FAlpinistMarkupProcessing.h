#pragma once

#include "CoreMinimal.h"
#include "Framework/Text/IRichTextMarkupParser.h"

class FAlpinistMarkupParser : public IRichTextMarkupParser
{
public:
	static TSharedRef< FAlpinistMarkupParser > Create();
	static TSharedRef< FAlpinistMarkupParser > GetStaticInstance();

public:
	virtual void Process(TArray<FTextLineParseResults>& Results, const FString& Input, FString& Output) override;

private:
	FAlpinistMarkupParser();
	
	void ParseLines(const FString& Input, const TArray<FTextRange>& LineRanges, TArray<FTextLineParseResults>& LineParseResultsArray) const;
	void HandleEscapeSequences(const FString& Input, TArray<FTextLineParseResults>& LineParseResultsArray, FString& ConcatenatedUnescapedLines) const;

	FRegexPattern EscapeSequenceRegexPattern;
	FRegexPattern ElementRegexPattern;
	FRegexPattern AttributeRegexPattern;
};

