#if (WITH_DEV_AUTOMATION_TESTS || WITH_PERF_AUTOMATION_TESTS)
#include "Campus/MiniGames/ButterflyGenerations/Core/ButterflyGenerationRegistry.h"
#include "ButterflyGenrationsClassicPositionValidatorTest.h"
#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FButterflyGenrationsClassicPositionValidatorTest, "Campus.ButterflyGenerations.GenerationsValidator.ClassicPosition",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)

bool FButterflyGenrationsClassicPositionValidatorTest::RunTest(const FString& Parameters)
{
	using namespace ButterflyGenerationsGame;
	std::vector<InheritanceConnection> connections = std::vector<InheritanceConnection>{};

	connections.push_back(InheritanceConnection({1, 1}, {0, 0}, {0, 1}));
	connections.push_back(InheritanceConnection({1, 2}, {0, 0}, {0, 1}));
	connections.push_back(InheritanceConnection({1, 3}, {0, 0}, {0, 1}));
	connections.push_back(InheritanceConnection({1, 4}, {0, 0}, {0, 1}));
	
	connections.push_back(InheritanceConnection({2, 0}, {1, 0}, {1, 1}));
	connections.push_back(InheritanceConnection({2, 1}, {1, 0}, {1, 1}));
	
	connections.push_back(InheritanceConnection({3, 0}, {2, 1}, {2, 2}));
	connections.push_back(InheritanceConnection({3, 1}, {2, 1}, {2, 2}));
	
	std::vector<uint8_t> layers = {2, 5, 3, 2};
		
	ButterflyGenerationRegistry* registry = new ButterflyGenerationRegistry({2, 5, 3, 2}, connections);

	AddInfo("TESTS WITH FILLED SLOTS AND DEFAULT CONNECTIONS:");
	/////////////////////////////////////////////////////////
	AddInfo("Solution with Error(parent properties not equals child).");
	
	registry->AddButterfly({0,0},{2,1,1});
	registry->AddButterfly({0,1},{2,3,2});
	
	registry->AddButterfly({1,0},{1,4,1});
	registry->AddButterfly({1,1},{1,5,1});
	registry->AddButterfly({1,2},{1,6,1});
	registry->AddButterfly({1,3},{1,7,1});
	registry->AddButterfly({1,4},{1,1,1});
	
	registry->AddButterfly({2,0},{1,1,1});
	registry->AddButterfly({2,1},{1,1,1});
	registry->AddButterfly({2,2},{1,1,1});
	
	registry->AddButterfly({3,0},{1,1,1});
	registry->AddButterfly({3,1},{1,1,1});
	
	TestTrueExpr(!registry->ValidateGenerations());
	//////////////////////////////////////////////////////////
	AddInfo("Solution without error(all properties equals each other).");
	
	registry->AddButterfly({0,0},{1,1,1});
	registry->AddButterfly({0,1},{1,1,1});
	
	registry->AddButterfly({1,0},{1,1,1});
	registry->AddButterfly({1,1},{1,1,1});
	registry->AddButterfly({1,2},{1,1,1});
	registry->AddButterfly({1,3},{1,1,1});
	registry->AddButterfly({1,4},{1,1,1});
	
	registry->AddButterfly({2,0},{1,1,1});
	registry->AddButterfly({2,1},{1,1,1});
	registry->AddButterfly({2,2},{1,1,1});
	
	registry->AddButterfly({3,0},{1,1,1});
	registry->AddButterfly({3,1},{1,1,1});
	
	TestTrueExpr(registry->ValidateGenerations());
	//////////////////////////////////////////////////////////
	AddInfo("Solution with different properties values.");
	
	registry->AddButterfly({0,0},{1,1,1});
	registry->AddButterfly({0,1},{2,2,2});
	
	registry->AddButterfly({1,0},{3,1,2});
	registry->AddButterfly({1,1},{1,2,1});
	registry->AddButterfly({1,2},{2,1,1});
	registry->AddButterfly({1,3},{1,2,2});
	registry->AddButterfly({1,4},{2,2,2});
	
	registry->AddButterfly({2,0},{3,2,1});
	registry->AddButterfly({2,1},{1,1,1});
	registry->AddButterfly({2,2},{2,2,2});
	
	registry->AddButterfly({3,0},{1,2,1});
	registry->AddButterfly({3,1},{2,1,2});
	
	TestTrueExpr(registry->ValidateGenerations());
	///////////////////////////////////////////////////////////
	AddInfo("Solution after removing one butterfly.");
	
	registry->RemoveButterfly({0,0});

	TestTrueExpr(!registry->ValidateGenerations());
	///////////////////////////////////////////////////////////
	
	return true;
}

#endif