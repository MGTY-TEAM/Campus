// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIHelpers.h"
#include "Campus/Inventory/InventoryActor.h"
#include "Components/ActorComponent.h"
#include "Containers/IntrusiveDoubleLinkedList.h"
#include "InventoryComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnSelectedItemChanged, AInventoryActor*);

class AInventoryActor;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CAMPUS_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInventoryComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;


	void SetInventoryActorAttachComponent(USceneComponent* AttachComponent);
	
	void AddItemAndSelect(AInventoryActor* Item);
	void SelectNextItem();
	void SelectPrevItem();
	void RemoveSelectedItem();
	
	FOnSelectedItemChanged OnSelectedItemChanged;
private:
	TDoubleLinkedList<AInventoryActor*> InventoryPool;

	AInventoryActor* SelectedInventoryActor{nullptr};

	USceneComponent* InventoryActorAttachComponent{nullptr};
};
