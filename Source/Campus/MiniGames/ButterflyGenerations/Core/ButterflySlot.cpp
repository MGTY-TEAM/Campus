#include "ButterflySlot.h"

ButterflyGenerationsGame::ButterflySlot::ButterflySlot(): M_Butterfly(nullptr), M_FirstSlotParent(nullptr), M_SecondSlotParent(nullptr)
{
}

ButterflyGenerationsGame::ButterflySlot::ButterflySlot(Butterfly* butterfly): M_Butterfly(butterfly), M_FirstSlotParent(nullptr),
                                                                              M_SecondSlotParent(nullptr)
{
}

ButterflyGenerationsGame::ButterflySlot::~ButterflySlot()
{
	delete M_Butterfly;
	delete M_FirstSlotParent;
	delete M_SecondSlotParent;
}

void ButterflyGenerationsGame::ButterflySlot::AddButterfly(Butterfly* butterfly)
{
	if (HasButterfly())
	{
		delete M_Butterfly;
	}
	M_Butterfly = butterfly;
}

void ButterflyGenerationsGame::ButterflySlot::RemoveButterfly()
{
	delete M_Butterfly;
	M_Butterfly = nullptr;
}

ButterflyGenerationsGame::Butterfly* ButterflyGenerationsGame::ButterflySlot::GetButterfly() const
{
	return M_Butterfly;
}

bool ButterflyGenerationsGame::ButterflySlot::HasButterfly() const
{
	return M_Butterfly != nullptr;
}

bool ButterflyGenerationsGame::ButterflySlot::IsValidDependency() const
{
	if (!HasButterfly())
		return false;


	if (!M_FirstSlotParent || !M_SecondSlotParent)
		return true;
            
	if (!M_FirstSlotParent->HasButterfly() || !M_SecondSlotParent->HasButterfly())
		return true;

           
	return ButterflyProperties::IsValidPropertiesChildToParents(
		M_Butterfly->GetProperties(), M_FirstSlotParent->GetButterfly()->GetProperties(),
		M_SecondSlotParent->GetButterfly()->GetProperties());
}

void ButterflyGenerationsGame::ButterflySlot::SetDependencySlots(ButterflySlot* firstParent,
	ButterflySlot* secondParent)
{
	M_FirstSlotParent = firstParent;
	M_SecondSlotParent = secondParent;
}
