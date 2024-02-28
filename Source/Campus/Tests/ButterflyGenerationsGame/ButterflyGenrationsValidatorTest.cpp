
#include "Campus/MiniGames/ButterflyGenerations/Core/Butterfly.h"
#if (WITH_DEV_AUTOMATION_TESTS || WITH_PERF_AUTOMATION_TESTS)
#include "ButterflyGenrationsValidatorTest.h"
#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FButterflyGenrationsValidatorTest, "Campus.ButterflyGenerationsGame.GenerationsValidator",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)

bool FButterflyGenrationsValidatorTest::RunTest( const FString& Parameters )
{
	using namespace ButterflyGenerationsGame;

	
	return true;
}

#endif