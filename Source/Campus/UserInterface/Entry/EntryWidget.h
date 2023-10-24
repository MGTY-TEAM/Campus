// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EntryWidget.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEntryExecuted, const FString&, Token);

class UButton;
class ULoginWidget;
class URegisterWidget;
class UTextBlock;
class UWidgetSwitcher;
/**
 * 
 */
UCLASS()
class CAMPUS_API UEntryWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	
	FOnEntryExecuted OnEntryExecute;

protected:
	
	virtual void NativeOnInitialized() override;
	
private:
	
	UPROPERTY(EditDefaultsOnly, Category = "Entry classes")
	TSubclassOf<ULoginWidget> LoginWidgetClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Entry classes")
	TSubclassOf<URegisterWidget> RegisterWidgetClass;

	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* WidgetSwitcher;

	UPROPERTY(meta = (BindWidget))
	UButton* SwitchEntryTypeButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SwitchEntryTypeButtonText;
	
	UPROPERTY()
	ULoginWidget* M_LoginWidget;
	
    UPROPERTY()
	URegisterWidget* M_RegisterWidget;

	UFUNCTION()
	void OnSwitchEntryTypeButtonClicked();

	UFUNCTION()
	void OnLoginExecute(const FString& Token);

	UFUNCTION()
	void OnRegisterExecute(const FString& Token);
	
};
