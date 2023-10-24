// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FormFieldsValidatorLib.generated.h"


/**
 * 
 */
UCLASS()
class CAMPUS_API UFormFieldsValidatorLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * @brief Validates all registration fields.
	 * @param Login The login to be validated.
	 * @param Nickname The nickname to be validated.
	 * @param Email The email address to be validated.
	 * @param Password The password to be validated.
	 * @param ConfirmPassword The password confirmation to be checked against the original password.
	 * @return true if all fields are valid and the confirmed password matches the original; otherwise, false.
	 */
	UFUNCTION()
	static bool IsRegisterFieldsValid(const FText& Login, const FText& Nickname, const FText& Email,
	                                  const FText& Password, const FText& ConfirmPassword);

	/**
    * @brief Validates the login and password fields.
    * @param Login The login to be validated.
    * @param Password The password to be validated.
    * @return true if both the login and password fields are valid; otherwise, false.
    */
	UFUNCTION()
	static bool IsLoginFieldsValid(const FText& Login, const FText& Password);

	/**
	 * @brief Checks if the provided text field is a valid nickname.
	 * @param Nickname The nickname to be validated.
	 * @return true if the nickname is valid; otherwise, false.
	 */
	UFUNCTION()
	static bool IsValidNickname(const FText& Nickname);

	/**
	 * @brief Checks if the provided text field contains a valid email format.
	 * @param Email The email address to be validated.
	 * @return true if the email format is valid; otherwise, false.
	 */
	UFUNCTION()
	static bool IsValidEmail(const FText& Email);

	/**
	 * @brief Checks if the provided text field contains a valid password.
	 * @param Password The password to be validated.
	 * @return true if the password is valid; otherwise, false.
	 */
	UFUNCTION()
	static bool IsValidPassword(const FText& Password);

	/**
	 * @brief Checks if the confirmed password matches the original password.
	 * @param Password The original password.
	 * @param ConfirmPassword The confirmed password.
	 * @return true if the confirmed password matches the original; otherwise, false.
	 */
	UFUNCTION()
	static bool IsConfirmPasswordEqualPassword(const FText& Password, const FText& ConfirmPassword);

	/**
	 * @brief Checks if the provided text field contains a valid login format.
	 * @param Login The login information to be validated.
	 * @return true if the login format is valid; otherwise, false.
	 */
	UFUNCTION()
	static bool IsValidLogin(const FText& Login);
};
