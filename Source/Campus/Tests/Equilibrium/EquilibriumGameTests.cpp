#if WITH_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"
#include "Campus/MiniGames/Equilibrium/Core/EquilibriumGame.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FEquilibriumGameTests, "Campus.Equilibrium.EquilibriumGameTests",
                                 EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)

bool FEquilibriumGameTests::RunTest(const FString& Parameters)
{
	using namespace EquilibriumGame;
	
	vector<vector<int>> Cups;

	Cups.push_back(vector<int32> {0, 0, 0});
	Cups.push_back(vector<int32> {0, 0, 1});
	Cups.push_back(vector<int32> {0, 1});
	Cups.push_back(vector<int32> {1, 0});
	Cups.push_back(vector<int32> {1, 1, 0});
	Cups.push_back(vector<int32> {1, 1, 1});

	AddInfo("Initialization check");
	GameEquilibrium *EquilibriumScale = new GameEquilibrium(Cups);
	TestTrue("Equilibrium isn't created correctly", EquilibriumScale->EquilibriumIsValidByCups(Cups));
	TestTrue("Expected start game", EquilibriumScale->TryStartGame());

	AddInfo("Checking for impossible additions");
	TestTrue("Expected that you can't add here weight {}", !EquilibriumScale->GetEquilibriumInstance().TryAddWeight({}, 5));
	TestTrue("Expected that you can't add here weight { 0 }", !EquilibriumScale->GetEquilibriumInstance().TryAddWeight({ 0 }, 5));
	TestTrue("Expected that you can't add here weight { 1 }", !EquilibriumScale->GetEquilibriumInstance().TryAddWeight({ 1 }, 5));
	TestTrue("Expected that you can't add here weight { 0, 0 }", !EquilibriumScale->GetEquilibriumInstance().TryAddWeight({ 0, 0 }, 5));
	TestTrue("Expected that you can't add here weight { 1, 1 }", !EquilibriumScale->GetEquilibriumInstance().TryAddWeight({ 1, 1 }, 5));
	TestTrue("Expected that you can't add here weight { 0, 1, 0}", !EquilibriumScale->GetEquilibriumInstance().TryAddWeight({ 0, 1, 0}, 5));
	TestTrue("Expected that you can't add here weight { 0, 1, 1 }", !EquilibriumScale->GetEquilibriumInstance().TryAddWeight({ 0, 1, 1 }, 5));
	TestTrue("Expected that you can't add here weight { 1, 0, 0 }", !EquilibriumScale->GetEquilibriumInstance().TryAddWeight({ 1, 0, 0 }, 5));
	TestTrue("Expected that you can't add here weight { 1, 0, 1 }", !EquilibriumScale->GetEquilibriumInstance().TryAddWeight({ 1, 0, 1 }, 5));

	AddInfo("Checking for possible additions");
	for (auto Cup : Cups)
	{
		TestTrue("Expected that you can add here weight ", EquilibriumScale->GetEquilibriumInstance().TryAddWeight(Cup, 2));
		if (Cup != Cups.back())
		{
			TestTrue("Expected that all cups aren't fill", !EquilibriumScale->GetEquilibriumInstance().EveryCupHasWeight());
		}
	}
	TestTrue("Expected that all cups are fill", EquilibriumScale->GetEquilibriumInstance().EveryCupHasWeight());
	TestTrue("Expected that you can't win if you fill all cups but equilibrium isn't stable", !EquilibriumScale->CheckWin());

	AddInfo("Checking for possible removing");
	for (auto Cup : Cups)
	{
		TestTrue("Expected that you can remove here weight ", EquilibriumScale->GetEquilibriumInstance().TryRemoveWeight(Cup));
		if (Cup != Cups.front())
		{
			TestTrue("Expected that all cups aren't fill", !EquilibriumScale->GetEquilibriumInstance().EveryCupHasWeight());
		}
	}
	TestTrue("Expected that you can remove weight", EquilibriumScale->GetEquilibriumInstance().TryRemoveWeight({1, 1, 1}));

	AddInfo("Checking for possible additions (the second try)");
	for (auto Cup : Cups)
	{
		TestTrue("Expected that you can add here weight ", EquilibriumScale->GetEquilibriumInstance().TryAddWeight(Cup, 5));
	}
	AddInfo("Checking for possible additions to the occupied cups");
	TestTrue("Expected that you can add here weight ", EquilibriumScale->GetEquilibriumInstance().TryAddWeight({ 0, 1 }, 10));
	TestTrue("Expected that you can add here weight ", EquilibriumScale->GetEquilibriumInstance().TryAddWeight( { 1, 0 }, 10));

	AddInfo("Checking for win");
	TestTrue("Expected that you win", EquilibriumScale->CheckWin());
	
	return true;
}

#endif
