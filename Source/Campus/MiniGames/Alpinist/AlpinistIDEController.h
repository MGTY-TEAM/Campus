
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AlpinistIDEController.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CAMPUS_API UAlpinistIDEController : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAlpinistIDEController();

protected:
	virtual void BeginPlay() override;

public:	
	
};
