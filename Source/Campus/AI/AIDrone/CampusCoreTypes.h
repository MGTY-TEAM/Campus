#pragma once

UENUM(BlueprintType)
enum class EActionType : uint8
{
	Idle			UMETA(DisplayName = "Idle"),
	GoHome			UMETA(DisplayName = "GoHome"),
	Pickup			UMETA(DisplayName = "Pickup")
};