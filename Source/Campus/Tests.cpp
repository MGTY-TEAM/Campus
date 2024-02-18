// Fill out your copyright notice in the Description page of Project Settings.


#include "Tests.h"
#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FMathMaxInt, "Campus.Math.MaxInt", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)


bool FMathMaxInt::RunTest(const FString& Parameters)
{
	FMath::Max(13, 25);

	TestTrue("2 different positive number", FMath::Max(13, 25) == 5);
	return true;
}
