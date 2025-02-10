// Fill out your copyright notice in the Description page of Project Settings.


#include "PanalButtonsWidget.h"
#include "PanalWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Campus/IncentiveSystem/QuestSystem/QuestManager.h"
#include "Campus/Interfaces/MiniGames/MiniGameInfo.h"
#include "Engine/AssetManager.h"
#define BINARY_TREE_DEBUG = false

void UPanalButtonsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Zero = WidgetTree->ConstructWidget<UButton>(UButton::StaticClass(), TEXT("Zero"));
	One = WidgetTree->ConstructWidget<UButton>(UButton::StaticClass(), TEXT("One"));
	Two = WidgetTree->ConstructWidget<UButton>(UButton::StaticClass(), TEXT("Two"));
	Three = WidgetTree->ConstructWidget<UButton>(UButton::StaticClass(), TEXT("Three"));
	Four = WidgetTree->ConstructWidget<UButton>(UButton::StaticClass(), TEXT("Four"));
	Five = WidgetTree->ConstructWidget<UButton>(UButton::StaticClass(), TEXT("Five"));
	Six = WidgetTree->ConstructWidget<UButton>(UButton::StaticClass(), TEXT("Six"));
	Seven = WidgetTree->ConstructWidget<UButton>(UButton::StaticClass(), TEXT("Seven"));
	Eight = WidgetTree->ConstructWidget<UButton>(UButton::StaticClass(), TEXT("Eight"));

	Buttons.Add(Zero);
	Buttons.Add(One);
	Buttons.Add(Two);
	Buttons.Add(Three);
	Buttons.Add(Four);
	Buttons.Add(Five);
	Buttons.Add(Six);
	Buttons.Add(Seven);
	Buttons.Add(Eight);

	Zero->OnClicked.AddDynamic(this, &UPanalButtonsWidget::ZeroClick);
	One->OnClicked.AddDynamic(this, &UPanalButtonsWidget::OneClick);
	Two->OnClicked.AddDynamic(this, &UPanalButtonsWidget::TwoClick);
	Three->OnClicked.AddDynamic(this, &UPanalButtonsWidget::ThreeClick);
	Four->OnClicked.AddDynamic(this, &UPanalButtonsWidget::FourClick);
	Five->OnClicked.AddDynamic(this, &UPanalButtonsWidget::FiveClick);
	Six->OnClicked.AddDynamic(this, &UPanalButtonsWidget::SixClick);
	Seven->OnClicked.AddDynamic(this, &UPanalButtonsWidget::SevenClick);
	Eight->OnClicked.AddDynamic(this, &UPanalButtonsWidget::EightClick);

	Images.Add(UAppleBrush.GetResourceObject());
	Images.Add(BananaBrush.GetResourceObject());
	Images.Add(BlueBrush.GetResourceObject());
	Images.Add(CherryBrush.GetResourceObject());
	Images.Add(GrapeBrush.GetResourceObject());
	Images.Add(OrangeBrush.GetResourceObject());
	Images.Add(PineBrush.GetResourceObject());
	Images.Add(StrawberryBrush.GetResourceObject());
	Images.Add(PearBrush.GetResourceObject());
	
	ImagesYes.Add(YesUAppleBrush.GetResourceObject());
	ImagesYes.Add(YesBananaBrush.GetResourceObject());
	ImagesYes.Add(YesBlueBrush.GetResourceObject());
	ImagesYes.Add(YesCherryBrush.GetResourceObject());
	ImagesYes.Add(YesGrapeBrush.GetResourceObject());
	ImagesYes.Add(YesOrangeBrush.GetResourceObject());
	ImagesYes.Add(YesPineBrush.GetResourceObject());
	ImagesYes.Add(YesStrawberryBrush.GetResourceObject());
	ImagesYes.Add(YesPearBrush.GetResourceObject());

	UMiniGameInfo* GameInfo = NewObject<UMiniGameInfo>();
	MiniGameInfo = GameInfo;

	if(MiniGameInfo)
	{
		MiniGameInfo->Title = "Бинарное дерево";
	}
	// Аналогично для ImagesYes
	//FSlateBrush ButtonImage;
	/*ButtonImage.SetResourceObject(LoadObject<UObject>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/Mesh/BinaryTree/FruitsPanel/UApple.UApple'")));
	Images.Add(ButtonImage.GetResourceObject());
	Zero->WidgetStyle.Normal.SetResourceObject(ButtonImage.GetResourceObject());
	
	ButtonImage.SetResourceObject(LoadObject<UObject>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/Mesh/BinaryTree/FruitsPanel/Banana.Banana'")));
	Images.Add(ButtonImage.GetResourceObject());
	One->WidgetStyle.Normal.SetResourceObject(ButtonImage.GetResourceObject());
	
	ButtonImage.SetResourceObject(LoadObject<UObject>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/Mesh/BinaryTree/FruitsPanel/Blue.Blue'")));
	Images.Add(ButtonImage.GetResourceObject());
	Two->WidgetStyle.Normal.SetResourceObject(ButtonImage.GetResourceObject());
	
	ButtonImage.SetResourceObject(LoadObject<UObject>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/Mesh/BinaryTree/FruitsPanel/Cherry.Cherry'")));
	Images.Add(ButtonImage.GetResourceObject());
	Three->WidgetStyle.Normal.SetResourceObject(ButtonImage.GetResourceObject());
	
	ButtonImage.SetResourceObject(LoadObject<UObject>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/Mesh/BinaryTree/FruitsPanel/Grape.Grape'")));
	Images.Add(ButtonImage.GetResourceObject());
	Four->WidgetStyle.Normal.SetResourceObject(ButtonImage.GetResourceObject());
	
	ButtonImage.SetResourceObject(LoadObject<UObject>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/Mesh/BinaryTree/FruitsPanel/Orange.Orange'")));
	Images.Add(ButtonImage.GetResourceObject());
	Five->WidgetStyle.Normal.SetResourceObject(ButtonImage.GetResourceObject());
	
	ButtonImage.SetResourceObject(LoadObject<UObject>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/Mesh/BinaryTree/FruitsPanel/Pine.Pine'")));
	Images.Add(ButtonImage.GetResourceObject());
	Six->WidgetStyle.Normal.SetResourceObject(ButtonImage.GetResourceObject());
	
	ButtonImage.SetResourceObject(LoadObject<UObject>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/Mesh/BinaryTree/FruitsPanel/Strawberry.Strawberry'")));
	Images.Add(ButtonImage.GetResourceObject());
	Seven->WidgetStyle.Normal.SetResourceObject(ButtonImage.GetResourceObject());
	
	ButtonImage.SetResourceObject(LoadObject<UObject>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/Mesh/BinaryTree/FruitsPanel/Pear.Pear'")));
	Images.Add(ButtonImage.GetResourceObject());
	Eight->WidgetStyle.Normal.SetResourceObject(ButtonImage.GetResourceObject());
	
	
	ButtonImage.SetResourceObject(LoadObject<UObject>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/Mesh/BinaryTree/FruitsPanel/YesUApple.YesUApple'")));
	ImagesYes.Add(ButtonImage.GetResourceObject());

	ButtonImage.SetResourceObject(LoadObject<UObject>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/Mesh/BinaryTree/FruitsPanel/YesBanana.YesBanana'")));
	ImagesYes.Add(ButtonImage.GetResourceObject());
	
	ButtonImage.SetResourceObject(LoadObject<UObject>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/Mesh/BinaryTree/FruitsPanel/YesBlue.YesBlue'")));
	ImagesYes.Add(ButtonImage.GetResourceObject());

	ButtonImage.SetResourceObject(LoadObject<UObject>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/Mesh/BinaryTree/FruitsPanel/YesCherry.YesCherry'")));
	ImagesYes.Add(ButtonImage.GetResourceObject());

	ButtonImage.SetResourceObject(LoadObject<UObject>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/Mesh/BinaryTree/FruitsPanel/YesGrape.YesGrape'")));
	ImagesYes.Add(ButtonImage.GetResourceObject());
	
	ButtonImage.SetResourceObject(LoadObject<UObject>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/Mesh/BinaryTree/FruitsPanel/YesOrange.YesOrange'")));
	ImagesYes.Add(ButtonImage.GetResourceObject());

	ButtonImage.SetResourceObject(LoadObject<UObject>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/Mesh/BinaryTree/FruitsPanel/YesPine.YesPine'")));
	ImagesYes.Add(ButtonImage.GetResourceObject());

	ButtonImage.SetResourceObject(LoadObject<UObject>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/Mesh/BinaryTree/FruitsPanel/YesStrawberry.YesStrawberry'")));
	ImagesYes.Add(ButtonImage.GetResourceObject());

	ButtonImage.SetResourceObject(LoadObject<UObject>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/Mesh/BinaryTree/FruitsPanel/YesPear.YesPear'")));
	ImagesYes.Add(ButtonImage.GetResourceObject());*/

	SyncImg();

	RandomWork.AddDynamic(this, &UPanalButtonsWidget::RandomMyImages);
}

void UPanalButtonsWidget::SyncImg()
{
	Zero->SynchronizeProperties();
	One->SynchronizeProperties();
	Two->SynchronizeProperties();
	Three->SynchronizeProperties();
	Four->SynchronizeProperties();
	Five->SynchronizeProperties();
	Six->SynchronizeProperties();
	Seven->SynchronizeProperties();
	Eight->SynchronizeProperties();
}

void UPanalButtonsWidget::RandomMyImages()
{
	if(Buttons.Num() != 0 && Images.Num() != 0 && ImagesYes.Num() !=0){
		R = FMath::RandRange(0, 8);
		for (int i = 0; i < 9; i++)
		{
			while (i == R)
			{
				R = FMath::RandRange(0, 8);
			}
			Buttons[i]->WidgetStyle.Normal.SetResourceObject(Images[R]);
			Buttons[R]->WidgetStyle.Normal.SetResourceObject(Images[i]);

			Buttons[i]->WidgetStyle.Hovered.SetResourceObject(Images[R]);
			Buttons[R]->WidgetStyle.Hovered.SetResourceObject(Images[i]);
		
			ImageOld = Images[i];
			Images[i] = Images[R];
			Images[R] = ImageOld;

			ImageOld = ImagesYes[i];
			ImagesYes[i] = ImagesYes[R];
			ImagesYes[R] = ImageOld;

			OldN = MyButtonsInt[i];
			MyButtonsInt[i] = MyButtonsInt[R];
			MyButtonsInt[R] = OldN;
			R = FMath::RandRange(0, 8);
		}
		SyncImg();
	}
	
}

void UPanalButtonsWidget::ButtonClick(int32 N)
{
	if (Panel->RightAnswer.Num() != 0 && Buttons[N]->GetIsEnabled() && Buttons.Num() != 0)
	{
		if (Panel->RightAnswer[AnswerNumber] == MyButtonsInt[N])
		{
			RightAnswers++;
#ifdef BINARY_TREE_DEBUG
			UE_LOG(LogTemp, Warning, TEXT("Right"));
#endif
			
		}
		AnswerNumber++;
#ifdef BINARY_TREE_DEBUG
		UE_LOG(LogTemp, Warning, TEXT("Номер %d"), MyButtonsInt[N]);
#endif
		Buttons[N]->WidgetStyle.Normal.SetResourceObject(ImagesYes[N]);
		Buttons[N]->WidgetStyle.Hovered.SetResourceObject(ImagesYes[N]);
		Buttons[N]->SetIsEnabled(false);
		Buttons[N]->SynchronizeProperties();

		if (AnswerNumber == 3)
		{
			CheckAnswers();
		}
		else
		{
			PlaySound(ClickButton);
		}
	}
}

void UPanalButtonsWidget::SetToOriginalImage()
{
	for (int i = 0; i < Buttons.Num(); ++i)
	{
		Buttons[i]->WidgetStyle.Normal.SetResourceObject(Images[i]);
		Buttons[i]->WidgetStyle.Hovered.SetResourceObject(Images[i]);
	}
}


void UPanalButtonsWidget::ZeroClick()
{
	ButtonClick(0);
}

void UPanalButtonsWidget::OneClick()
{
	ButtonClick(1);
}

void UPanalButtonsWidget::TwoClick()
{
	ButtonClick(2);
}

void UPanalButtonsWidget::ThreeClick()
{
	ButtonClick(3);
}

void UPanalButtonsWidget::FourClick()
{
	ButtonClick(4);
}

void UPanalButtonsWidget::FiveClick()
{
	ButtonClick(5);
}

void UPanalButtonsWidget::SixClick()
{
	ButtonClick(6);
}

void UPanalButtonsWidget::SevenClick()
{
	ButtonClick(7);
}

void UPanalButtonsWidget::EightClick()
{
	ButtonClick(8);
}

void UPanalButtonsWidget::CheckAnswers()
{
	for (int i = 0; i < Buttons.Num(); ++i)
	{
		Buttons[i]->SetIsEnabled(true);
	}
	if (RightAnswers == 3)
	{
#ifdef BINARY_TREE_DEBUG
		UE_LOG(LogTemp, Warning, TEXT("You win"));
#endif
		
		RandomWorkEnd.Broadcast();
		RightAnswers = 0;
		AnswerNumber = 0;
		PlaySound(GameEndRight);
		SetToOriginalImage();
		ExecuteMiniGameCompleted.Broadcast(MiniGameInfo);
		UQuestManager::CompleteQuest("BinaryTree");
	}
	else
	{
#ifdef BINARY_TREE_DEBUG
		UE_LOG(LogTemp, Warning, TEXT("You lose"));
# endif
		RightAnswers = 0;
		AnswerNumber = 0;
		PlaySound(GameNotEnd);
		SetToOriginalImage();
		ExecuteMiniGameError.Broadcast();
	}
}
