// Fill out your copyright notice in the Description page of Project Settings.


#include "PanalButtonsWidget.h"
#include "PanalWidget.h"
#include "Blueprint/WidgetTree.h"


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

	FSlateBrush ButtonImage;
	
	ButtonImage.SetResourceObject(LoadObject<UObject>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/Mesh/BinaryTree/FruitsPanel/UApple.UApple'")));
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
	

	Zero->SynchronizeProperties();
	One->SynchronizeProperties();
	Two->SynchronizeProperties();
	Three->SynchronizeProperties();
	Four->SynchronizeProperties();
	Five->SynchronizeProperties();
	Six->SynchronizeProperties();
	Seven->SynchronizeProperties();
	Eight->SynchronizeProperties();
	
	RandomWork.AddDynamic(this , &UPanalButtonsWidget::RandomMyImages);
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
	R = FMath::RandRange(0,8);
	for (int i = 0; i < 9; i++)
	{
		while (i==R)
		{
			R = FMath::RandRange(0,8);
		}
		Buttons[i]->WidgetStyle.Normal.SetResourceObject(Images[R]);
		Buttons[R]->WidgetStyle.Normal.SetResourceObject(Images[i]);
		ImageOld = Images[i];
		Images[i] = Images[R];
		Images[R] = ImageOld;
		OldN = MyButtonsInt[i];
		MyButtonsInt[i]=R;
		MyButtonsInt[R]=OldN;
		R = FMath::RandRange(0,8);
	}
	SyncImg();
}

void UPanalButtonsWidget::ZeroClick()
{
	if(Panel->RightAnswer[AnswerNumber] == MyButtonsInt[0])
	{
		RightAnswers++;
		UE_LOG(LogTemp, Warning, TEXT("Right"));
	}
	AnswerNumber++;
	
	if (AnswerNumber==3)
	{
		CheckAnswers();
	}
}

void UPanalButtonsWidget::OneClick()
{
	if(Panel->RightAnswer[AnswerNumber] == MyButtonsInt[1])
	{
		RightAnswers++;
		UE_LOG(LogTemp, Warning, TEXT("Right"));
	}
	AnswerNumber++;
	if (AnswerNumber==3)
	{
		CheckAnswers();
	}
}

void UPanalButtonsWidget::TwoClick()
{
	if(Panel->RightAnswer[AnswerNumber] == MyButtonsInt[2])
	{
		RightAnswers++;UE_LOG(LogTemp, Warning, TEXT("Right"));
	}
	AnswerNumber++;
	if (AnswerNumber==3)
	{
		CheckAnswers();
	}
}

void UPanalButtonsWidget::ThreeClick()
{
	if(Panel->RightAnswer[AnswerNumber] == MyButtonsInt[3])
	{
		RightAnswers++;UE_LOG(LogTemp, Warning, TEXT("Right"));
	}
	AnswerNumber++;
	if (AnswerNumber==3)
	{
		CheckAnswers();
	}
}

void UPanalButtonsWidget::FourClick()
{
	if(Panel->RightAnswer[AnswerNumber] == MyButtonsInt[4])
	{
		RightAnswers++;UE_LOG(LogTemp, Warning, TEXT("Right"));
	}
	AnswerNumber++;
	if (AnswerNumber==3)
	{
		CheckAnswers();
	}
}

void UPanalButtonsWidget::FiveClick()
{
	if(Panel->RightAnswer[AnswerNumber] == MyButtonsInt[5])
	{
		RightAnswers++;UE_LOG(LogTemp, Warning, TEXT("Right"));
	}
	AnswerNumber++;
	if (AnswerNumber==3)
	{
		CheckAnswers();
	}
}

void UPanalButtonsWidget::SixClick()
{
	if(Panel->RightAnswer[AnswerNumber] == MyButtonsInt[6])
	{
		RightAnswers++;UE_LOG(LogTemp, Warning, TEXT("Right"));
	}
	AnswerNumber++;
	if (AnswerNumber==3)
	{
		CheckAnswers();
	}
}

void UPanalButtonsWidget::SevenClick()
{
	if(Panel->RightAnswer[AnswerNumber] == MyButtonsInt[7])
	{
		RightAnswers++;UE_LOG(LogTemp, Warning, TEXT("Right"));
	}
	AnswerNumber++;
	if (AnswerNumber==3)
	{
		CheckAnswers();
	}
}

void UPanalButtonsWidget::EightClick()
{
	if(Panel->RightAnswer[AnswerNumber] == MyButtonsInt[8])
	{
		RightAnswers++;UE_LOG(LogTemp, Warning, TEXT("Right"));
	}
	AnswerNumber++;

	if (AnswerNumber==3)
	{
		CheckAnswers();
	}
}

void UPanalButtonsWidget::CheckAnswers()
{
	if(RightAnswers==3)
	{
		UE_LOG(LogTemp, Warning, TEXT("You win"));
		Execute.ExecuteIfBound();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("You lose"));
		RightAnswers=0;
		AnswerNumber=0;
	}
}





