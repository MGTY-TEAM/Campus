// Fill out your copyright notice in the Description page of Project Settings.


#include "FormFieldsValidatorLib.h"

bool UFormFieldsValidatorLib::IsRegisterFieldsValid(const FText& Login, const FText& Nickname, const FText& Email,
                                                    const FText& Password, const FText& ConfirmPassword)
{
	if (IsValidLogin(Login) && IsValidNickname(Nickname) && IsValidEmail(Email) && IsValidPassword(Password))
	{
		return IsConfirmPasswordEqualPassword(Password, ConfirmPassword);
	}
	return false;
}

bool UFormFieldsValidatorLib::IsLoginFieldsValid(const FText& Login, const FText& Password)
{
	return IsValidLogin(Login) && IsValidPassword(Password);
}

bool UFormFieldsValidatorLib::IsValidNickname(const FText& Nickname)
{
	FString StringNickname = Nickname.ToString();
	if (StringNickname.Len() < 3 || StringNickname.Len() > 32)
	{
		return false;
	}

	for (const TCHAR Char : StringNickname)
	{
		if (!FChar::IsAlnum(Char)) 
		{
			return false;
		}
	}
	return true;
}

bool UFormFieldsValidatorLib::IsValidEmail(const FText& Email)
{
	const FString StringEmail = Email.ToString();
	
	int32 AtIndex;
	if (StringEmail.FindChar('@', AtIndex) && StringEmail.FindChar('.', AtIndex) && AtIndex > 0)
	{
		return true;
	}
	return false;
}

bool UFormFieldsValidatorLib::IsValidPassword(const FText& Password)
{
	const FString StringPassword = Password.ToString();
	if (StringPassword.Len() < 8)
	{
		return false;
	}
	return true;
}

bool UFormFieldsValidatorLib::IsConfirmPasswordEqualPassword(const FText& Password, const FText& ConfirmPassword)
{
	const FString StringPassword = Password.ToString();
	const FString StringConfirmPassword = ConfirmPassword.ToString();
	if (StringPassword != StringConfirmPassword)
	{
		return false;
	}
	return true;
}

bool UFormFieldsValidatorLib::IsValidLogin(const FText& Login)
{
	const FString StringLogin = Login.ToString();
    if (StringLogin.Len() < 3 || StringLogin.Len() > 32)
    {
        return false;
    }

    for (const TCHAR Char : StringLogin)
    {
        if (!FChar::IsAlnum(Char)) 
        {
            return false;
        }
    }
    return true;
}
