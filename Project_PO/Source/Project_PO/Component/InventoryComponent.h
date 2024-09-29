// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseActorComponent.h"
#include "../MyStructureAll.h"
#include "InventoryComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnInventoryUpdated);

USTRUCT()
struct FResult
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	int32 Index;

	UPROPERTY(VisibleAnywhere)
	bool IsFindItem;
};

UCLASS()
class PROJECT_PO_API UInventoryComponent : public UBaseActorComponent
{
	GENERATED_BODY()
	
public:
	UInventoryComponent();

private:
	int32 InventorySize;
	E_ItemType ItemType;
	bool IsAddFailed;

	int32 AmountLeft;
	FSlot LocalSlot;

	TMap<E_ItemType, TArray<FSlot>> SlotMap;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	FOnInventoryUpdated OnInventoryUpdated;

	TArray<FSlot> GetSlots() { return *SlotMap.Find(ItemType); }

	void SetSlot(int32 _Index, FSlot _Slot) { 
		if (SlotMap.Contains(ItemType) && SlotMap[ItemType].IsValidIndex(_Index))
			SlotMap[ItemType][_Index] = _Slot;
	};

	FSlot GetSlot(int32 _Index) { 
		if (TArray<FSlot>* SlotArray = SlotMap.Find(ItemType))
		{
			if (SlotArray->IsValidIndex(_Index))
				return (*SlotArray)[_Index];
		}
		return FSlot();
	}

	//void SetSlots(const TArray<FSlot>& _Slots);

	//void UsePotionSlot(int32 _Index);

	void AddItem(int32 ItemID, int32 ItemAmount, FSpawnItemType Type);
	void DropItem(int32 TargetIndex);

	FResult FindSlot(int32 ItemID);
	FResult CheckSlotEmpty();

	int32 GetStackSize(int32 ItemID);
	void IncreaseSlotStack(int32 Index, int32 Amount);

	void AddToNewSlot(int32 ItemID, int32 ItemAmount, FSpawnItemType Type);
	void ChangeSlot(int32 BeforeIndex, int32 TargetIndex, UInventoryComponent* BeforeInvenCom);

};
