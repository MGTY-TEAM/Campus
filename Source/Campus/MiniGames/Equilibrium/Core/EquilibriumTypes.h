#pragma once

namespace EquilibriumTypes
{
	enum ENodeRotationState
	{
		NRS_Stable = 0,
		NRS_Left = 1,
		NRS_Right = 2
	};

	class EquilElement
	{
	protected:
		virtual ~EquilElement();
		int Weight = 0;
		
	public:
		virtual int CalculateMass() = 0;

		int GetMass() const { return Weight; }

		EquilElement* GetLeftChild() const { return LeftChild; }
		EquilElement* GetRightChild() const { return RightChild; }

		void SetLeftChild(EquilElement* Element);
		void SetRightChild(EquilElement* Element);

	private:
		EquilElement* LeftChild = nullptr;
		EquilElement* RightChild = nullptr;
	};

	class EquilNode : public EquilElement
	{
	public:
		EquilNode();
		
		virtual int CalculateMass() override;

		ENodeRotationState GetRotationState() const { return RotationState; }

	private:
		ENodeRotationState RotationState;
	};

	class EquilCup : public EquilElement
	{
	public:
		EquilCup();
		void AddWeight(int NewWeight);
		void RemoveWeight();
		virtual int CalculateMass() override;
	};
}