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

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	class UPotionQuickSlotComponent* QuickSlotComponent;

private:
	int32 InventorySize;
	E_ItemType ItemType;
	bool IsAddFailed;

	int32 AmountLeft;
	FSlot LocalSlot;

	TMap<E_ItemType, TArray<FSlot>> SlotMap;

private:
	FResult CheckSlotEmpty(E_ItemType Type);
	int32 GetStackSize(int32 ItemID);
	void IncreaseSlotStack(int32 Index, int32 Amount, E_ItemType Type);
	void AddToNewSlot(int32 ItemID, int32 ItemAmount, FSpawnItemType Type);
	void CheckSlotAmount(int32 Index, E_ItemType Type);

public:
	FOnInventoryUpdated OnInventoryUpdated;

	TArray<FSlot> GetSlots() { return *SlotMap.Find(ItemType); }

	void SetSlot(int32 _Index, FSlot _Slot, E_ItemType Type) {
		if (SlotMap.Contains(Type) && SlotMap[Type].IsValidIndex(_Index))
			SlotMap[Type][_Index] = _Slot;
	};

	FSlot GetSlot(int32 _Index, E_ItemType Type) {
		if (TArray<FSlot>* SlotArray = SlotMap.Find(Type))
		{
			if (SlotArray->IsValidIndex(_Index))
				return (*SlotArray)[_Index];
		}
		return FSlot();
	}

	//void SetSlots(const TArray<FSlot>& _Slots);

	//void UsePotionSlot(int32 _Index);

	void AddItem(int32 ItemID, int32 ItemAmount, FSpawnItemType Type);
	void DropItem(int32 TargetIndex, FSpawnItemType Type);

	FResult FindSlot(int32 ItemID, E_ItemType Type);
	
	void ChangeSlot(int32 BeforeIndex, int32 TargetIndex, UInventoryComponent* BeforeInvenCom);

	void SetItemType(E_ItemType _ItemType) { ItemType = _ItemType; }
	void SetQuickSlotComponent(class UPotionQuickSlotComponent* _QuickSlotComponent) { QuickSlotComponent = _QuickSlotComponent; }

	void ChangeEquip(int32 Index,int32 ItemID);
	void UseItem(int32 Index, FSpawnItemType Type);
	void UseCunsumItem(int32 Index, E_ItemType Type);
	void UseEtcItem(int32 Index, FSpawnItemType Type);
	void UseInstallEtcItem(int32 Index, E_ItemType Type);
	void CheckUseItemAmount(int32 ItemID, E_ItemType Type);

	void RegisterQuickSlot(int32 Index);
	int32 CheckFullItemAmount(int32 ItemID);
};
