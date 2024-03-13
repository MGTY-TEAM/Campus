
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AEquilElement.generated.h"

UCLASS()
class CAMPUS_API AAEquilElement : public AActor
{
	GENERATED_BODY()
	
public:	
	AAEquilElement();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Equilibrium")
	USceneComponent* SceneComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* StaticMeshComponent;
	
	int32_t Weight;

public:	
	virtual void Tick(float DeltaTime) override;

	int32_t GetMass() const { return Weight; }

	AAEquilElement* GetLeftChild() const { return LeftChild; }
	AAEquilElement* GetRightChild() const { return RightChild; }

	void SetLeftChild(AAEquilElement* Element);
	void SetRightChild(AAEquilElement* Element);

	UStaticMeshComponent* GetStaticMesh() const { return StaticMeshComponent; }
private:
	UPROPERTY()
	AAEquilElement* LeftChild = nullptr;
	UPROPERTY()
	AAEquilElement* RightChild = nullptr;
};
