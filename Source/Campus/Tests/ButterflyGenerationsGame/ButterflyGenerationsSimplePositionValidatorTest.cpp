#if (WITH_DEV_AUTOMATION_TESTS || WITH_PERF_AUTOMATION_TESTS)
#include "ButterflyGenerationsSimplePositionValidatorTest.h"
#include "Campus/MiniGames/ButterflyGenerations/Core/ButterflyGenerationRegistry.h"
#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FButterflyGenerationsSimplePositionValidatorTest, "Campus.ButterflyGenerations.GenerationsValidator.SimplePosition",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)

bool FButterflyGenerationsSimplePositionValidatorTest::RunTest(const FString& Parameters)
{
	using namespace ButterflyGenerationsGame;
	std::vector<InheritanceConnection> connections;
	
	connections.push_back(InheritanceConnection({1, 1}, {0, 0}, {0, 1}));
	
	ButterflyGenerationRegistry* registry = new ButterflyGenerationRegistry({2, 1}, connections);
	///////////////////////////////////////////////////////////
	AddInfo("TEST WITH SIMPLE 2 LAYERS GENERATIONS:");

	////////////////////////////////////////////////////////////
	AddInfo("Solution with zero butterfly");

	TestTrueExpr(!registry->ValidateGenerations());
	////////////////////////////////////////////////////////////
	AddInfo("Solution with one added butterfly");
	
	registry->AddButterfly({0, 0}, {1, 1, 1});

	TestTrueExpr(!registry->ValidateGenerations());
	////////////////////////////////////////////////////////////
	AddInfo("Solution with two added butterflies");

	registry->AddButterfly({0, 1}, {2, 2, 2});

	TestTrueExpr(!registry->ValidateGenerations());
	////////////////////////////////////////////////////////////
	AddInfo("Solution with three added butterflies");

	registry->AddButterfly({1, 0}, {2, 1, 2});
	
	TestTrueExpr(registry->ValidateGenerations());
	////////////////////////////////////////////////////////////
	return true;
}

#endif