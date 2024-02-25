// ChatManager.h

#pragma once
#define CHAT_MANAGER_DEBUG false

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ChatManager.generated.h"

// Declare a logging category for the ChatManager class
DECLARE_LOG_CATEGORY_CLASS(LogChatManager, Log, Log);

// Forward declaration of UChatUserComponent class
class UChatUserComponent;

/**
 * Manages the chat functionality of the application.
 * Allows users to register, send messages, and retrieve user lists.
 */
UCLASS()
class CAMPUS_API UChatManager : public UObject
{
    GENERATED_BODY()

public:
    UChatManager(); // Default constructor
    
    /**
     * Retrieves the instance of the ChatManager singleton.
     *
     * @return The instance of the ChatManager.
     */
    static UChatManager* Get();
    
    /**
     * Registers a user with the ChatManager.
     *
     * @param UserID The unique identifier of the user to register.
     * @param User A pointer to the ChatUserComponent associated with the user.
     * @return True if the user is successfully registered, false otherwise.
     */
    bool RegisterUser(const FName& UserID, UChatUserComponent* User);
    
    /**
     * Sends a chat message from one user to another.
     *
     * @param SenderID The unique identifier of the user sending the message.
     * @param ReceiverID The unique identifier of the user receiving the message.
     * @param Message The content of the message to be sent.
     */
    void SendChatMessage(const FName& SenderID, const FName& ReceiverID, const FText& Message);

protected:
    // Overrides the BeginDestroy method of UObject
    virtual void BeginDestroy() override;

private:
    // Pointer to the singleton instance of ChatManager
    static UChatManager* ChatManagerInstance;

    // Map of registered users with their unique identifiers
    TMap<FName, UChatUserComponent*> RegisteredUsers;
    
    /**
     * Validates whether a user with the given UserID is registered.
     *
     * @param UserID The unique identifier of the user to validate.
     * @return True if the user is registered, false otherwise.
     */
    bool ValidateUserID(const FName& UserID) const;
};
