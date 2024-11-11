#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateStyleRegistry.h"

class FEmptySlateStyle
{
public:
	static void Initialize()
	{
		if (!StyleSet.IsValid())
		{
			StyleSet = MakeShareable(new FSlateStyleSet("EmptyStyle"));

			const FSlateFontInfo RobotoBoldFont = FCoreStyle::GetDefaultFontStyle("Regular", 24);
			StyleSet->Set("EmptySlateStyle.Empty", FTextBlockStyle()
				.SetFont(RobotoBoldFont)
				.SetColorAndOpacity(FSlateColor(FLinearColor(1.f, 1.f, 1.f, 0.0f)))
				.SetSelectedBackgroundColor(FSlateColor(FLinearColor(0.f, 1.f, 0.f, 0.25f))));
		}
		FSlateStyleRegistry::RegisterSlateStyle(*StyleSet);
	}

	static const ISlateStyle& Get() { return *StyleSet; }
	static void Delete()
	{
		if (StyleSet.IsValid())
		{
			FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet);
			StyleSet.Reset();
		}
	}
private:
	static TSharedPtr<FSlateStyleSet> StyleSet;
};

class FMainCodeSlateStyle
{
public:
	static void Initialize()
	{
		if (!StyleSet.IsValid())
		{
			StyleSet = MakeShareable(new FSlateStyleSet("MainCodeStyle"));

			const FSlateFontInfo RobotoBoldFont = FCoreStyle::GetDefaultFontStyle("Regular", 24);
			StyleSet->Set("MainCodeSlateStyle.MainText", FTextBlockStyle()
				.SetFont(RobotoBoldFont)
				.SetColorAndOpacity(FSlateColor(FLinearColor(1.f, 1.f, 1.f, 1.0f))));
			FSlateStyleRegistry::RegisterSlateStyle(*StyleSet);
		}
	}

	static const ISlateStyle& Get() { return *StyleSet; }
	static void Delete()
	{
		if (StyleSet.IsValid())
		{
			FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet);
			StyleSet.Reset();
		}
	}
private:
	static TSharedPtr<FSlateStyleSet> StyleSet;
};

class FSimpleCommandSlateStyle
{
public:
	static void Initialize()
	{
		if (!StyleSet.IsValid())
		{
			StyleSet = MakeShareable(new FSlateStyleSet("SimpleCommand"));

			const FSlateFontInfo RobotoBoldFont = FCoreStyle::GetDefaultFontStyle("Regular", 24);
			StyleSet->Set("FSimpleCommandSlateStyle.SimpleCommand", FTextBlockStyle()
				.SetFont(RobotoBoldFont)
				//.SetColorAndOpacity(FSlateColor(FLinearColor(0.4f, 0.9f, 0.9f, 1.0f))));
				.SetColorAndOpacity(FSlateColor(FLinearColor(0.05f, 0.7f, 0.05f, 1.0f))));
			FSlateStyleRegistry::RegisterSlateStyle(*StyleSet);
		}
	}

	static const ISlateStyle& Get() { return *StyleSet; }
	static void Delete()
	{
		if (StyleSet.IsValid())
		{
			FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet);
			StyleSet.Reset();
		}
	}
private:
	static TSharedPtr<FSlateStyleSet> StyleSet;
};

class FConditionCommandSlateStyle
{
public:
	static void Initialize()
	{
		if (!StyleSet.IsValid())
		{
			StyleSet = MakeShareable(new FSlateStyleSet("ConditionCommand"));

			const FSlateFontInfo RobotoBoldFont = FCoreStyle::GetDefaultFontStyle("Regular", 24);
			StyleSet->Set("FConditionCommandSlateStyle.ConditionCommand", FTextBlockStyle()
				.SetFont(RobotoBoldFont)
				.SetColorAndOpacity(FSlateColor(FLinearColor(0.87f, 0.1f, 0.87f, 1.0f))));
			FSlateStyleRegistry::RegisterSlateStyle(*StyleSet);
		}
	}

	static const ISlateStyle& Get() { return *StyleSet; }
	static void Delete()
	{
		if (StyleSet.IsValid())
		{
			FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet);
			StyleSet.Reset();
		}
	}
private:
	static TSharedPtr<FSlateStyleSet> StyleSet;
};

class FCheckCommandSlateStyle
{
public:
	static void Initialize()
	{
		if (!StyleSet.IsValid())
		{
			StyleSet = MakeShareable(new FSlateStyleSet("CheckCommand"));

			const FSlateFontInfo RobotoBoldFont = FCoreStyle::GetDefaultFontStyle("Regular", 24);
			StyleSet->Set("FCheckCommandSlateStyle.CheckCommand", FTextBlockStyle()
				.SetFont(RobotoBoldFont)
				//.SetColorAndOpacity(FSlateColor(FLinearColor(0.4f, 0.9f, 0.9f, 1.0f))));
				.SetColorAndOpacity(FSlateColor(FLinearColor(0.2f, 0.15f, 1.f, 1.0f))));
			FSlateStyleRegistry::RegisterSlateStyle(*StyleSet);
		}
	}

	static const ISlateStyle& Get() { return *StyleSet; }
	static void Delete()
	{
		if (StyleSet.IsValid())
		{
			FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet);
			StyleSet.Reset();
		}
	}
private:
	static TSharedPtr<FSlateStyleSet> StyleSet;
};

class FScopeCommandSlateStyle
{
public:
	static void Initialize()
	{
		if (!StyleSet.IsValid())
		{
			StyleSet = MakeShareable(new FSlateStyleSet("ScopeCommand"));

			const FSlateFontInfo RobotoBoldFont = FCoreStyle::GetDefaultFontStyle("Regular", 24);
			StyleSet->Set("FScopeCommandSlateStyle.ScopeCommand", FTextBlockStyle()
				.SetFont(RobotoBoldFont)
				//.SetColorAndOpacity(FSlateColor(FLinearColor(0.4f, 0.9f, 0.9f, 1.0f))));
				.SetColorAndOpacity(FSlateColor(FLinearColor(0.8f, 0.8f, 0.8f, 1.0f))));
			FSlateStyleRegistry::RegisterSlateStyle(*StyleSet);
		}
	}

	static const ISlateStyle& Get() { return *StyleSet; }
	static void Delete()
	{
		if (StyleSet.IsValid())
		{
			FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet);
			StyleSet.Reset();
		}
	}
private:
	static TSharedPtr<FSlateStyleSet> StyleSet;
};

class FNegateCommandSlateStyle
{
public:
	static void Initialize()
	{
		if (!StyleSet.IsValid())
		{
			StyleSet = MakeShareable(new FSlateStyleSet("NegateCommand"));

			const FSlateFontInfo RobotoBoldFont = FCoreStyle::GetDefaultFontStyle("Regular", 24);
			StyleSet->Set("FNegateCommandSlateStyle.NegateCommand", FTextBlockStyle()
				.SetFont(RobotoBoldFont)
				//.SetColorAndOpacity(FSlateColor(FLinearColor(0.4f, 0.9f, 0.9f, 1.0f))));
				.SetColorAndOpacity(FSlateColor(FLinearColor(0.8f, 0.05f, 0.05f, 1.0f))));
			FSlateStyleRegistry::RegisterSlateStyle(*StyleSet);
		}
	}

	static const ISlateStyle& Get() { return *StyleSet; }
	static void Delete()
	{
		if (StyleSet.IsValid())
		{
			FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet);
			StyleSet.Reset();
		}
	}
private:
	static TSharedPtr<FSlateStyleSet> StyleSet;
};

// ------------------------------------ Small

class FMainCodeSlateStyleSmall
{
public:
	static void Initialize()
	{
		if (!StyleSet.IsValid())
		{
			StyleSet = MakeShareable(new FSlateStyleSet("MainCodeStyleSmall"));

			const FSlateFontInfo RobotoBoldFont = FCoreStyle::GetDefaultFontStyle("Regular", 16);
			StyleSet->Set("MainCodeSlateStyleSmall.MainText", FTextBlockStyle()
				.SetFont(RobotoBoldFont)
				.SetColorAndOpacity(FSlateColor(FLinearColor(1.f, 1.f, 1.f, 1.0f))));
			FSlateStyleRegistry::RegisterSlateStyle(*StyleSet);
		}
	}

	static const ISlateStyle& Get() { return *StyleSet; }
	static void Delete()
	{
		if (StyleSet.IsValid())
		{
			FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet);
			StyleSet.Reset();
		}
	}
private:
	static TSharedPtr<FSlateStyleSet> StyleSet;
};

class FSimpleCommandSlateStyleSmall
{
public:
	static void Initialize()
	{
		if (!StyleSet.IsValid())
		{
			StyleSet = MakeShareable(new FSlateStyleSet("SimpleCommandSmall"));

			const FSlateFontInfo RobotoBoldFont = FCoreStyle::GetDefaultFontStyle("Regular", 16);
			StyleSet->Set("FSimpleCommandSlateStyleSmall.SimpleCommand", FTextBlockStyle()
				.SetFont(RobotoBoldFont)
				//.SetColorAndOpacity(FSlateColor(FLinearColor(0.4f, 0.9f, 0.9f, 1.0f))));
				.SetColorAndOpacity(FSlateColor(FLinearColor(0.05f, 0.7f, 0.05f, 1.0f))));
			FSlateStyleRegistry::RegisterSlateStyle(*StyleSet);
		}
	}

	static const ISlateStyle& Get() { return *StyleSet; }
	static void Delete()
	{
		if (StyleSet.IsValid())
		{
			FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet);
			StyleSet.Reset();
		}
	}
private:
	static TSharedPtr<FSlateStyleSet> StyleSet;
};

class FConditionCommandSlateStyleSmall
{
public:
	static void Initialize()
	{
		if (!StyleSet.IsValid())
		{
			StyleSet = MakeShareable(new FSlateStyleSet("ConditionCommandSmall"));

			const FSlateFontInfo RobotoBoldFont = FCoreStyle::GetDefaultFontStyle("Regular", 16);
			StyleSet->Set("FConditionCommandSlateStyleSmall.ConditionCommand", FTextBlockStyle()
				.SetFont(RobotoBoldFont)
				.SetColorAndOpacity(FSlateColor(FLinearColor(0.87f, 0.1f, 0.87f, 1.0f))));
			FSlateStyleRegistry::RegisterSlateStyle(*StyleSet);
		}
	}

	static const ISlateStyle& Get() { return *StyleSet; }
	static void Delete()
	{
		if (StyleSet.IsValid())
		{
			FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet);
			StyleSet.Reset();
		}
	}
private:
	static TSharedPtr<FSlateStyleSet> StyleSet;
};

class FCheckCommandSlateStyleSmall
{
public:
	static void Initialize()
	{
		if (!StyleSet.IsValid())
		{
			StyleSet = MakeShareable(new FSlateStyleSet("CheckCommandSmall"));

			const FSlateFontInfo RobotoBoldFont = FCoreStyle::GetDefaultFontStyle("Regular", 16);
			StyleSet->Set("FCheckCommandSlateStyleSmall.CheckCommand", FTextBlockStyle()
				.SetFont(RobotoBoldFont)
				//.SetColorAndOpacity(FSlateColor(FLinearColor(0.4f, 0.9f, 0.9f, 1.0f))));
				.SetColorAndOpacity(FSlateColor(FLinearColor(0.2f, 0.15f, 1.f, 1.0f))));
			FSlateStyleRegistry::RegisterSlateStyle(*StyleSet);
		}
	}

	static const ISlateStyle& Get() { return *StyleSet; }
	static void Delete()
	{
		if (StyleSet.IsValid())
		{
			FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet);
			StyleSet.Reset();
		}
	}
private:
	static TSharedPtr<FSlateStyleSet> StyleSet;
};

class FScopeCommandSlateStyleSmall
{
public:
	static void Initialize()
	{
		if (!StyleSet.IsValid())
		{
			StyleSet = MakeShareable(new FSlateStyleSet("ScopeCommandSmall"));

			const FSlateFontInfo RobotoBoldFont = FCoreStyle::GetDefaultFontStyle("Regular", 16);
			StyleSet->Set("FScopeCommandSlateStyleSmall.ScopeCommand", FTextBlockStyle()
				.SetFont(RobotoBoldFont)
				//.SetColorAndOpacity(FSlateColor(FLinearColor(0.4f, 0.9f, 0.9f, 1.0f))));
				.SetColorAndOpacity(FSlateColor(FLinearColor(0.8f, 0.8f, 0.8f, 1.0f))));
			FSlateStyleRegistry::RegisterSlateStyle(*StyleSet);
		}
	}

	static const ISlateStyle& Get() { return *StyleSet; }
	static void Delete()
	{
		if (StyleSet.IsValid())
		{
			FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet);
			StyleSet.Reset();
		}
	}
private:
	static TSharedPtr<FSlateStyleSet> StyleSet;
};

class FNegateCommandSlateStyleSmall
{
public:
	static void Initialize()
	{
		if (!StyleSet.IsValid())
		{
			StyleSet = MakeShareable(new FSlateStyleSet("NegateCommandSmall"));

			const FSlateFontInfo RobotoBoldFont = FCoreStyle::GetDefaultFontStyle("Regular", 16);
			StyleSet->Set("FNegateCommandSlateStyleSmall.NegateCommand", FTextBlockStyle()
				.SetFont(RobotoBoldFont)
				//.SetColorAndOpacity(FSlateColor(FLinearColor(0.4f, 0.9f, 0.9f, 1.0f))));
				.SetColorAndOpacity(FSlateColor(FLinearColor(0.8f, 0.05f, 0.05f, 1.0f))));
			FSlateStyleRegistry::RegisterSlateStyle(*StyleSet);
		}
	}

	static const ISlateStyle& Get() { return *StyleSet; }
	static void Delete()
	{
		if (StyleSet.IsValid())
		{
			FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet);
			StyleSet.Reset();
		}
	}
private:
	static TSharedPtr<FSlateStyleSet> StyleSet;
};

// -------------------------------------------------------------------------------------
class FMySlateBrush
{
public:
	static void Initialize(UTexture2D* NewTexture)
	{
		if (!MySlateBrush.IsValid())
		{
			if (NewTexture)
			{
				TArray<FColor> Pixels;
				Pixels.SetNum(1000 * 1000);  // Задаём нужный размер массива

				for (int32 i = 0; i < Pixels.Num(); i++)
				{
					Pixels[i] = FColor(18, 18, 18);
				}
		
				// ---------------------------------------------------------- Градиент -----------------------------------------------------------------------
				/*for (int32 Y = 0; Y < 1000; Y++)
				{
					for (int32 X = 0; X < 1000; X++)
					{
						// Линейная интерполяция между StartColor и EndColor
						float Alpha = static_cast<float>(X) / static_cast<float>(1000 - 1);
		
						uint8 R = FMath::Lerp(FColor::Red.R, FColor::Green.R, Alpha);
						uint8 G = FMath::Lerp(FColor::Red.G, FColor::Green.G, Alpha);
						uint8 B = FMath::Lerp(FColor::Red.B, FColor::Green.B, Alpha);
						uint8 A = FMath::Lerp(FColor::Red.A, FColor::Green.A, Alpha);
						
						FColor PixelColor = FColor(R, G, B, A);
		
						// Задаём цвет пикселя
						Pixels[Y * 1000 + X] = PixelColor;
					}
				}*/
		
				// Обновляем текстуру с данными пикселей
				void* TextureData = NewTexture->GetPlatformData()->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
				FMemory::Memcpy(TextureData, Pixels.GetData(), Pixels.Num() * sizeof(FColor));
				NewTexture->GetPlatformData()->Mips[0].BulkData.Unlock();

				// Обновляем текстуру
				NewTexture->UpdateResource();

				MySlateBrush = MakeShared<FSlateBrush>();
				MySlateBrush->SetResourceObject(NewTexture);
				MySlateBrush->ImageSize = FVector2D(1000, 1000);
			}
		}
	}

	static FSlateBrush& Get() { return *MySlateBrush; }
	static void Delete()
	{
		if (MySlateBrush.IsValid())
		{
			MySlateBrush.Reset();
		}
	}
private:
	static TSharedPtr<FSlateBrush> MySlateBrush;
};

class FMainSlateBrush
{
public:
	static void Initialize(UTexture2D* NewTexture)
	{
		if (!MySlateBrush.IsValid())
		{
			if (NewTexture)
			{
				TArray<FColor> Pixels;
				Pixels.SetNum(1000 * 1000);  // Задаём нужный размер массива

				for (int32 i = 0; i < Pixels.Num(); i++)
				{
					Pixels[i] = FColor(23, 23, 23);
				}
				
				void* TextureData = NewTexture->GetPlatformData()->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
				FMemory::Memcpy(TextureData, Pixels.GetData(), Pixels.Num() * sizeof(FColor));
				NewTexture->GetPlatformData()->Mips[0].BulkData.Unlock();

				// Обновляем текстуру
				NewTexture->UpdateResource();

				MySlateBrush = MakeShared<FSlateBrush>();
				MySlateBrush->SetResourceObject(NewTexture);
				MySlateBrush->ImageSize = FVector2D(1000, 1000);
			}
		}
	}

	static FSlateBrush& Get() { return *MySlateBrush; }
	static void Delete()
	{
		if (MySlateBrush.IsValid())
		{
			MySlateBrush.Reset();
		}
	}
private:
	static TSharedPtr<FSlateBrush> MySlateBrush;
};

class FMovableSlateBrush
{
public:
	static void Initialize(UTexture2D* NewTexture)
	{
		if (!MySlateBrush.IsValid())
		{
			if (NewTexture)
			{
				TArray<FColor> Pixels;
				Pixels.SetNum(700 * 1000);  // Задаём нужный размер массива

				for (int32 i = 0; i < Pixels.Num(); i++)
				{
					Pixels[i] = FColor(35, 35, 35);
				}
				
				void* TextureData = NewTexture->GetPlatformData()->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
				FMemory::Memcpy(TextureData, Pixels.GetData(), Pixels.Num() * sizeof(FColor));
				NewTexture->GetPlatformData()->Mips[0].BulkData.Unlock();

				// Обновляем текстуру
				NewTexture->UpdateResource();

				MySlateBrush = MakeShared<FSlateBrush>();
				MySlateBrush->SetResourceObject(NewTexture);
				MySlateBrush->ImageSize = FVector2D(700, 1000);
			}
		}
	}

	static FSlateBrush& Get() { return *MySlateBrush; }
	static void Delete()
	{
		if (MySlateBrush.IsValid())
		{
			MySlateBrush.Reset();
		}
	}
private:
	static TSharedPtr<FSlateBrush> MySlateBrush;
};