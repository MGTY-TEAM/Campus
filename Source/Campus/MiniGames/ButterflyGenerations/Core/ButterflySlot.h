#pragma once
#include "Butterfly.h"

namespace ButterflyGenerationsGame
{
	class ButterflySlot
	{
	public:

        ButterflySlot();

        ButterflySlot(Butterfly* butterfly);

        ~ButterflySlot();

        void AddButterfly(Butterfly* butterfly);

        void RemoveButterfly();

        Butterfly* GetButterfly() const;

        bool HasButterfly() const;

        bool IsValidDependency() const;

        void SetDependencySlots(ButterflySlot* firstParent, ButterflySlot* secondParent);

    private:
		Butterfly* M_Butterfly;
		ButterflySlot* M_FirstSlotParent;
		ButterflySlot* M_SecondSlotParent;
	};
}

