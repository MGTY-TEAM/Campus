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

			const FSlateFontInfo RobotoBoldFont = FCoreStyle::GetDefaultFontStyle("Regular", 36);
			StyleSet->Set("EmptySlateStyle.Empty", FTextBlockStyle()
				.SetFont(RobotoBoldFont)
				.SetColorAndOpacity(FSlateColor(FLinearColor(1.f, 1.f, 1.f, 0.0f))));
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

			const FSlateFontInfo RobotoBoldFont = FCoreStyle::GetDefaultFontStyle("Regular", 36);
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

			const FSlateFontInfo RobotoBoldFont = FCoreStyle::GetDefaultFontStyle("Regular", 36);
			StyleSet->Set("FSimpleCommandSlateStyle.SimpleCommand", FTextBlockStyle()
				.SetFont(RobotoBoldFont)
				//.SetColorAndOpacity(FSlateColor(FLinearColor(0.4f, 0.9f, 0.9f, 1.0f))));
				.SetColorAndOpacity(FSlateColor(FLinearColor(1.f, 0.f, 0.f, 1.0f))));
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

			const FSlateFontInfo RobotoBoldFont = FCoreStyle::GetDefaultFontStyle("Regular", 36);
			StyleSet->Set("FConditionCommandSlateStyle.ConditionCommand", FTextBlockStyle()
				.SetFont(RobotoBoldFont)
				.SetColorAndOpacity(FSlateColor(FLinearColor(0.f, 0.f, 1.f, 1.0f))));
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