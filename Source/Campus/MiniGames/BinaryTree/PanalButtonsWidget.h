// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniMinic.h"
#include "PanalWidget.h"
#include "Blueprint/UserWidget.h"
#include "Campus/Interfaces/MiniGames/BinaryFruit/BinaryFruit.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "PanalButtonsWidget.generated.h"

/**
 * 
 */
UCLASS()
class CAMPUS_API UPanalButtonsWidget : public UUserWidget , public IBinaryFruit , public  IMiniGames
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
	void ZeroClick();
	
	UFUNCTION(BlueprintCallable)
	void OneClick();

	UFUNCTION(BlueprintCallable)
	void TwoClick();

	UFUNCTION(BlueprintCallable)
	void ThreeClick();

	UFUNCTION(BlueprintCallable)
	void FourClick();

	UFUNCTION(BlueprintCallable)
	void FiveClick();

	UFUNCTION(BlueprintCallable)
	void SixClick();

	UFUNCTION(BlueprintCallable)
	void SevenClick();

	UFUNCTION(BlueprintCallable)
	void EightClick();
	UFUNCTION(BlueprintCallable)
	void CheckAnswers();

	UPROPERTY(meta = (BindWidget))
	UButton* Zero;
	
	UPROPERTY(meta = (BindWidget))
	UButton* One;

	UPROPERTY(meta = (BindWidget))
	UButton* Two;
	
	UPROPERTY(meta = (BindWidget))
	UButton* Three;

	UPROPERTY(meta = (BindWidget))
	UButton* Four;

	UPROPERTY(meta = (BindWidget))
	UButton* Five;
	
	UPROPERTY(meta = (BindWidget))
	UButton* Six;
	
	UPROPERTY(meta = (BindWidget))
	UButton* Seven;

	UPROPERTY(meta = (BindWidget))
	UButton* Eight;

	APanalWidget* Panel = Cast<APanalWidget>(UGameplayStatics::GetActorOfClass(GetWorld(), APanalWidget::StaticClass()));

	
	virtual void NativeConstruct() override;
	
	TArray<UObject*> Images;
	TArray<UObject*> ImagesYes;
	TArray<UButton*> Buttons;
	TArray<int32> MyButtonsInt {0,1,2,3,4,5,6,7,8};
	UObject* ImageOld;
	int32 R=0;
	int32 OldN=0;
	void SyncImg();
	
	UFUNCTION(BlueprintCallable)
	void RandomMyImages();

	void ButtonClick(int32 N);

	void SetToOriginalImage();
	
	USoundBase* ClickButton = LoadObject<USoundBase>(nullptr, TEXT("/Script/Engine.SoundWave'/Game/Sounds/MiniGames/BinaryTree/najatie-na-kompyuternuyu-knopku1.najatie-na-kompyuternuyu-knopku1'"));
	USoundBase* GameEndRight = LoadObject<USoundBase>(nullptr, TEXT("/Script/Engine.SoundWave'/Game/Sounds/MiniGames/BinaryTree/GameEndRight.GameEndRight'"));
	USoundBase* GameNotEnd = LoadObject<USoundBase>(nullptr, TEXT("/Script/Engine.SoundWave'/Game/Sounds/MiniGames/BinaryTree/GameNotEnd.GameNotEnd'"));
public:
	UPROPERTY(BlueprintAssignable , BlueprintCallable , BlueprintReadWrite)
	FRandom RandomWorkEnd;

	UPROPERTY(BlueprintReadWrite)
	int32 AnswerNumber = 0;
	UPROPERTY(BlueprintReadWrite)
	int32 RightAnswers = 0;

	UPROPERTY(EditDefaultsOnly, Category="Images")
	FSlateBrush UAppleBrush;
	UPROPERTY(EditDefaultsOnly, Category="Images")
	FSlateBrush BananaBrush;
	UPROPERTY(EditDefaultsOnly, Category="Images")
	FSlateBrush BlueBrush;
	UPROPERTY(EditDefaultsOnly, Category="Images")
	FSlateBrush CherryBrush;
	UPROPERTY(EditDefaultsOnly, Category="Images")
	FSlateBrush GrapeBrush;
	UPROPERTY(EditDefaultsOnly, Category="Images")
	FSlateBrush OrangeBrush;
	UPROPERTY(EditDefaultsOnly, Category="Images")
	FSlateBrush PineBrush;
	UPROPERTY(EditDefaultsOnly, Category="Images")
	FSlateBrush StrawberryBrush;
	UPROPERTY(EditDefaultsOnly, Category="Images")
	FSlateBrush PearBrush;
	
	UPROPERTY(EditDefaultsOnly, Category="Images")
	FSlateBrush YesUAppleBrush;
	UPROPERTY(EditDefaultsOnly, Category="Images")
	FSlateBrush YesBananaBrush;
	UPROPERTY(EditDefaultsOnly, Category="Images")
	FSlateBrush YesBlueBrush;
	UPROPERTY(EditDefaultsOnly, Category="Images")
	FSlateBrush YesCherryBrush;
	UPROPERTY(EditDefaultsOnly, Category="Images")
	FSlateBrush YesGrapeBrush;
	UPROPERTY(EditDefaultsOnly, Category="Images")
	FSlateBrush YesOrangeBrush;
	UPROPERTY(EditDefaultsOnly, Category="Images")
	FSlateBrush YesPineBrush;
	UPROPERTY(EditDefaultsOnly, Category="Images")
	FSlateBrush YesStrawberryBrush;
	UPROPERTY(EditDefaultsOnly, Category="Images")
	FSlateBrush YesPearBrush;
	
};
