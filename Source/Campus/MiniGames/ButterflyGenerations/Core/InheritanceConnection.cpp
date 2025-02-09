#include "InheritanceConnection.h"

ButterflyGenerationsGame::InheritanceConnection::InheritanceConnection(std::pair<int, int> child,
	std::pair<int, int> firstParent, std::pair<int, int> secondParent):
	Child(child), FirstParent(firstParent), SecondParent(secondParent)
{
}
