// ChatUserComponent.h

#pragma once
#define CHAT_USER_COMPONENT_DEBUG false;

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ChatUserComponent.generated.h"



class UMessageInstance;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnMessageReceived, UMessageInstance*)
DEFINE_LOG_CATEGORY_STATIC(LogChatUserComponent, Log, Log);

/**
 * Represents a user component for handling chat functionality.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CAMPUS_API UChatUserComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UChatUserComponent(); // Default constructor

	/**
	 * Sets the unique identifier of the user.
	 *
	 * @param UserID The new unique identifier for the user.
	 */
	void SetUserID(const FName& UserID);
    
	/**
	 * Receives a chat message from another user.
	 *
	 * @param MessageInstance The instance of the message received.
	 */
	virtual void ReceiveMessage(UMessageInstance* MessageInstance);
    
	/**
	 * Sends a chat message to another user.
	 *
	 * @param ReceiverID The unique identifier of the user to send the message to.
	 * @param Message The content of the message to be sent.
	 */
	virtual void SendMessage(const FName& ReceiverID, const FText& Message);

	// Event delegate triggered when a message is received
	FOnMessageReceived OnMessageReceived;

private:
	FName M_UserID; // Unique identifier of the user
};