#pragma once

UENUM(BlueprintType)
enum class EActionType : uint8
{
	Leading			UMETA(DisplayName = "Leading"),
	Holding			UMETA(DisplayName = "Holding"),
	ListeningMusic	UMETA(DisplayName = "ListeningMusic"),
	ViewInfo		UMETA(DisplayName = "ViewInfo")
};