// MessageInstance.h

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MessageInstance.generated.h"

/**
 * Represents an instance of a chat message.
 */
UCLASS()
class CAMPUS_API UMessageInstance : public UObject
{
	GENERATED_BODY()

public:
	/**
	 * Retrieves information about the message.
	 *
	 * @return A tuple containing the sender ID, receiver ID, and message content.
	 */
	TTuple<FName, FName, FText> GetMessageInfo();
    
	/**
	 * Sets up the message with the provided details.
	 *
	 * @param NewSenderID The unique identifier of the message sender.
	 * @param NewReceiverID The unique identifier of the message receiver.
	 * @param NewMessage The content of the message.
	 */
	void SetupMessage(const FName& NewSenderID, const FName& NewReceiverID, const FText& NewMessage);

private:
	FName SenderID; // Unique identifier of the message sender
	FName ReceiverID; // Unique identifier of the message receiver
	FText Message; // Content of the message
};
