#pragma once

UENUM(BlueprintType)
enum class EActionType : uint8
{
	Teleport		UMETA(DisplayName = "Teleport"),
	Walk			UMETA(DisplayName = "Walk"),
	ViewInfo		UMETA(DisplayName = "ViewInfo")
};