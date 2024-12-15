
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AEquilElement.generated.h"

/**
 *	Base element for equilibrium.
 */

UCLASS()
class CAMPUS_API AAEquilElement : public AActor
{
	GENERATED_BODY()
	
public:	
	AAEquilElement();

protected:
	/**
	 * Root component for this element.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Equilibrium")
	USceneComponent* SceneComponent;

	/**
	 * Main StaticMesh for this element.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* StaticMeshComponent;

	/**
	 * StaticMesh for arm.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* StaticMeshComponentForArm;

public:
	/**
	 * Return for this element left child.
	 * @return Left child.
	 */
	AAEquilElement* GetLeftChild() const { return LeftChild; }
	/**
	 * Return for this element right child.
	 * @return Right child.
	 */
	AAEquilElement* GetRightChild() const { return RightChild; }

	/**
	 * Sets for this element left child.
	 * @param Element New left child. 
	 */
	void SetLeftChild(AAEquilElement* Element);
	/**
	 * Sets for this element right child.
	 * @param Element New right child.
	 */
	void SetRightChild(AAEquilElement* Element);

	/**
	 * Return Main StaticMesh for this element.
	 * @return StaticMeshComponent.
	 */
	UStaticMeshComponent* GetStaticMesh() const { return StaticMeshComponent; }
	/**
	 * Return StaticMeshForArm for this element.
	 * @return StaticMeshComponentForArm.
	 */
	UStaticMeshComponent* GetStaticMeshForArm() const { return StaticMeshComponentForArm; }
private:
	/**
	 * Left child of this element.
	 */
	UPROPERTY()
	AAEquilElement* LeftChild = nullptr;
	/**
	 * Right child of this element.
	 */
	UPROPERTY()
	AAEquilElement* RightChild = nullptr;
};
