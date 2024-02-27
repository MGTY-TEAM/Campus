#pragma once
#include "ButterflyProperties.h"


namespace ButterflyGenerationsGame
{
	class Butterfly
	{
	public:
		Butterfly(ButterflyGenerationsGame::ButterflyProperties butterflyProperties, Butterfly* firstParent = nullptr,
		          Butterfly* secondParent = nullptr);
		
		const ButterflyProperties& GetProperties() const;
		void SetProperties(const ButterflyProperties& butterflyProperties);
		
		bool IsParentsValid() const;

	private:
		ButterflyProperties M_ButterflyProperties;

		Butterfly* M_FirstParent;
		Butterfly* M_SecondParent;
	};
}
