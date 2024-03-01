#pragma once

#include <iostream>
#include <vector>
#include "EquilibriumTypes.h"

using namespace std;

namespace EquilibriumUtils
{
	static EquilElement* GetNeededElement(const vector<int>& Array, EquilElement* Root)
	{
		EquilElement* CurrentElement = Root;
		for (const auto Element : Array)
		{
			if (Element == 0)
			{
				CurrentElement = CurrentElement->GetLeftChild();
			}
			else
			{
				CurrentElement = CurrentElement->GetRightChild();
			}
		}
		return CurrentElement;
	}
}
