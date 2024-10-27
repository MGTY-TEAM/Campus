// UserGameInstance.h

#pragma once
#define USER_GAME_INSTANCE_DEBUG false

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "UserGameInstance.generated.h"

// Define a logging category for game instance logs
DEFINE_LOG_CATEGORY_STATIC(LogUserGameInstance, Log, Log);

/**
 * Represents user-specific information.
 */
USTRUCT(BlueprintType)
struct FUserInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "User")
	FString Nickname;

	UPROPERTY(BlueprintReadOnly, Category = "User")
	FString Email;

	UPROPERTY(BlueprintReadOnly, Category = "User")
	FString ID;
};

/**
 * Manages user-specific data and transitions between game states.
 */
UCLASS()
class CAMPUS_API UUserGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	/**
	 * Retrieves the user's ID.
	 *
	 * @return The user's ID.
	 */
	const FString& GetUserID() const;

	/**
	 * Retrieves the user's authentication token.
	 *
	 * @return The user's authentication token.
	 */
	const FString& GetUserToken() const;

	/**
	 * Retrieves the user's nickname.
	 *
	 * @return The user's nickname.
	 */
	const FString& GetNickname() const;

	/**
	 * Retrieves the user's email address.
	 *
	 * @return The user's email address.
	 */
	const FString& GetEmail() const;

	/**
	 * Sets the user's authentication token.
	 *
	 * @param Token The authentication token to set.
	 */
	void SetUserToken(const FString& Token);

	/**
	 * Attempts to retrieve user information and transition to the main menu.
	 *
	 * @return True if the attempt was successful, false otherwise.
	 */
	bool TryToGetAndFillUserInfoAndTransitToMainMenu();

protected:
	virtual void Init() override;

	virtual void LoadComplete(const float LoadTime, const FString& MapName) override;
	
	virtual void Shutdown() override;
	
	
	UPROPERTY(EditDefaultsOnly)
	UDataTable* QuestTable;	
private:
	FUserInfo M_UserInfo; // User information
	FString M_UserToken; // User authentication token
	FString M_GameServerPort; // Port for the game server
};
