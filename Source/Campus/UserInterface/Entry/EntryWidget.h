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
 * Widget for user entry (login or registration).
 */
UCLASS()
class CAMPUS_API UEntryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/** Event dispatcher for entry execution (login or registration). */
	UPROPERTY(BlueprintAssignable)
	FOnEntryExecuted OnEntryExecute;

protected:
	virtual void NativeOnInitialized() override;

private:
	/** Class of the login widget. */
	UPROPERTY(EditDefaultsOnly, Category = "Entry classes")
	TSubclassOf<ULoginWidget> LoginWidgetClass;

	/** Class of the register widget. */
	UPROPERTY(EditDefaultsOnly, Category = "Entry classes")
	TSubclassOf<URegisterWidget> RegisterWidgetClass;

	/** Widget switcher for switching between login and registration widgets. */
	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* WidgetSwitcher;

	/** Button for switching between login and registration views. */
	UPROPERTY(meta = (BindWidget))
	UButton* SwitchEntryTypeButton;

	/** Text block for displaying the current entry type (login or register). */
	UPROPERTY(meta = (BindWidget))
	UTextBlock* SwitchEntryTypeButtonText;

	/** Instance of the login widget. */
	UPROPERTY()
	ULoginWidget* M_LoginWidget;

	/** Instance of the register widget. */
	UPROPERTY()
	URegisterWidget* M_RegisterWidget;

	/** Callback function for the switch entry type button click event. */
	UFUNCTION()
	void OnSwitchEntryTypeButtonClicked();

	/** Callback function for login execution. */
	UFUNCTION()
	void OnLoginExecute(const FString& Token);

	/** Callback function for register execution. */
	UFUNCTION()
	void OnRegisterExecute(const FString& Token);
};

