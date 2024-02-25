// ChatBox.h

#pragma once

#include "CoreMinimal.h"
#include "TimerManager.h"
#include "Types/SlateEnums.h"
#include "Blueprint/UserWidget.h"
#include "Campus/Chat/MessageInstance.h"
#include "ChatBox.generated.h"

// Forward declarations
class UChatUserComponent;
class AAIAnimDrone;
class UMessageInstance;


// Declare delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTeleportationDelegate, int, index);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDarkeningDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessageDelegate, int, index);

/**
 * Represents the chat box widget.
 */
UCLASS()
class CAMPUS_API UChatBox : public UUserWidget
{
    GENERATED_BODY()

public:
    UChatUserComponent* OwnerChatUserComponent; // Pointer to the owner chat user component

    void ReceiveMessage(UMessageInstance* MessageInstance); // Receive a message from the chat

    void ConnectChatComponent(UChatUserComponent* ChatUserComponent); // Connect the chat component to the chat box
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget")
    TSubclassOf<UUserWidget> BlueprintWidgetClass; // Class of the chat widget

    AAIAnimDrone* Drone; // Pointer to the drone actor

    bool bCanRobotMoveToLocation = false; // Flag indicating whether the robot can move to a location

    // Widgets
    UPROPERTY(meta = (BindWidget))
    class UCanvasPanel* ParentPanel;
    UPROPERTY(meta = (BindWidget))
    class UCanvasPanel* ChatBox_Panel;
    UPROPERTY(meta = (BindWidget))
    class UImage* ChatBar_BG;
    UPROPERTY(meta = (BindWidget))
    class UImage* ChatIcon;
    UPROPERTY(meta = (BindWidget))
    class UImage* Chat_BG;
    UPROPERTY(meta = (BindWidget))
    class UEditableTextBox* SendMessage_TextBox;
    UPROPERTY(meta = (BindWidget))
    class UButton* SendMessage_Button;
    UPROPERTY(meta = (BindWidget))
    class UScrollBox* Chat_ScrollBox;

    // Delegates
    UPROPERTY(BlueprintAssignable, Category = "Dispatcher")
    FTeleportationDelegate TeleportationEvent;
    UPROPERTY(BlueprintAssignable, Category = "Dispatcher")
    FDarkeningDelegate DarkeningEvent;
    UPROPERTY(BlueprintAssignable, Category = "Dispatcher")
    FMessageDelegate SendMessageEvent;

protected:
    // Initializes the widget
    virtual bool Initialize() override;

    // Native construct method
    virtual void NativeConstruct() override;

    // Native destruct method
    virtual void NativeDestruct() override;

    // Callback for text box text committed event
    UFUNCTION()
    void OnTextBoxTextCommitted(const FText& Text, ETextCommit::Type CommitMethod);

    // Start teleportation process
    void StartTeleport(int index);

    // Set focus on text input
    void SetFocusOnTextInput();

    // Update chat messages
    void UpdateChatMessages(FText Message, FText Sender);
};
