// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Campus/Inventory/InventoryActor.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class UUInventoryWidget;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnSelectedItemChanged, AInventoryActor*);

class AInventoryActor;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CAMPUS_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInventoryComponent();

public:
	void ConnectInventoryWidget(UUInventoryWidget* InventoryWidget);
	void AddItemAndSelect(AInventoryActor* Item);
	void SelectNextItem();
	void SelectPrevItem();
	AInventoryActor* RemoveSelectedItem();
	bool IsEmpty() const;
	
	FOnSelectedItemChanged OnSelectedItemChanged;
private:
	void SelectItem(AInventoryActor* Item);
	void DeselectItem(AInventoryActor* Item);
	
	TDoubleLinkedList<AInventoryActor*> InventoryPool;
	
	AInventoryActor* SelectedInventoryActor{nullptr};
	
	UUInventoryWidget* M_InventoryWidget{nullptr};
	
};
