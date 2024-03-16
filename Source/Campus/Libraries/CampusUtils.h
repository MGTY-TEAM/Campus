#pragma once

class CampusUtils
{
public:
	static bool IsBinaryNumber(const FString& StringForCheck)
	{
		for (const auto Char : StringForCheck)
		{
			const int32 IntChar = FChar::ConvertCharDigitToInt(Char);
			if (IntChar != 0 && IntChar != 1)
			{
				return false;
			}
		}
		return true;
	}

	static std::vector<int32_t> FStringToVectorOfInt(const FString& StringToInt)
	{
		std::vector<int32_t> VectorInt;

		for (const auto CharToInt : StringToInt)
		{
			VectorInt.push_back(FChar::ConvertCharDigitToInt(CharToInt));
		}

		return VectorInt;
	}

	static std::vector<std::vector<int32_t>> TArrayOfFStringToVectorOfVectorOfInt(const TArray<FString>& TArrayToConv)
	{
		std::vector<std::vector<int32_t>> VectorOfVectorOfInt;

		for (auto StringToConv : TArrayToConv)
		{
			VectorOfVectorOfInt.push_back(FStringToVectorOfInt(StringToConv));
		}

		return VectorOfVectorOfInt;
	}
};
