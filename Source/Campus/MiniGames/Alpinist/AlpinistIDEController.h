
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AlpinistIDEController.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnAlpinistLogUpdate, void*)

class SMainAlpinistWidget;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CAMPUS_API UAlpinistIDEController : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAlpinistIDEController();

	FOnAlpinistLogUpdate OnAlpinistLogUpdate;
protected:
	virtual void BeginPlay() override;

	TSharedPtr<SMainAlpinistWidget> AlpinistWidget;
	TSharedPtr<SWidget> AlpinistWidgetContainer;
public:	
	bool InitializeAlpinistIDE();
	void OnSelectedLevel(int Level);
	void OnBuildButtonClick();
	void OnRunButtonClick();
	void OnToStartPositionButtonClick();
	void OnCloseGameButtonClick();
};
