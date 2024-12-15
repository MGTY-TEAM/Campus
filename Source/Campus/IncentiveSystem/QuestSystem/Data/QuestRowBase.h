#pragma once

#include "CoreMinimal.h"
#include "QuestRowBase.generated.h"

USTRUCT()
struct CAMPUS_API FQuestRowBase : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString QuestID;
		
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString QuestName;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString QuestDescription;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FString> SubQuestIDs;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FString> NextQuestIDs;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString ParentQuestID;
};
