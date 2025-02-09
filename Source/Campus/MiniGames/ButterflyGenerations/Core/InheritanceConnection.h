#pragma once

namespace ButterflyGenerationsGame
{
	struct InheritanceConnection
	{
		InheritanceConnection(std::pair<int, int> child, std::pair<int, int> firstParent, std::pair<int, int> secondParent);

		std::pair<int, int> Child;
		std::pair<int, int> FirstParent;
		std::pair<int, int> SecondParent;
	};
}

