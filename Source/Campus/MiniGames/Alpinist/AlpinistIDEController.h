
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
	void OnChangeCode(const FString& NewCode);
	void OnBuildButtonClick();
	void OnRunButtonClick();
	void OnClearLogButtonClick();
	void OnToStartPositionButtonClick();
	void OnQuitGameButtonClick();

	int32 GetSelectedLevel() const;
	TSet<int32> GetPassedLevels() const;
};
