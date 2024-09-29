// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "../Manager/BaseGameInstance.h"

UInventoryComponent::UInventoryComponent()
{
	InventorySize = 35;
	ItemType = E_ItemType::E_Equip;
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	TArray<FSlot> Slots;
	Slots.SetNum(InventorySize);
	Slots[0].ItemID = 1000;
	Slots[0].Amount = 1;
	SlotMap.Emplace(E_ItemType::E_Equip, Slots);
	Slots[0].ItemID = 1003;
	Slots[0].Amount = 1;
	SlotMap.Emplace(E_ItemType::E_Cunsumable, Slots);
	Slots[0].ItemID = 1005;
	Slots[0].Amount = 2;
	SlotMap.Emplace(E_ItemType::E_Etc, Slots);
}

void UInventoryComponent::AddItem(int32 ItemID, int32 ItemAmount, FSpawnItemType Type)
{
	AmountLeft = ItemAmount;

	FResult result;

	while (AmountLeft > 0 && !IsAddFailed)
	{
		result = FindSlot(ItemID);
		if (result.IsFindItem)
		{
			IncreaseSlotStack(result.Index, ItemAmount);
			AmountLeft--;
		}
		else
		{
			result = CheckSlotEmpty();
			if (result.IsFindItem)
			{
				AddToNewSlot(ItemID, ItemAmount, Type);
				AmountLeft--;
			}
			else
				IsAddFailed = true;
		}
	}
}

void UInventoryComponent::DropItem(int32 TargetIndex)
{
	TArray<FSlot>& ArrayRef = SlotMap[ItemType];
	ArrayRef[0] = FSlot();
}

FResult UInventoryComponent::FindSlot(int32 ItemID)
{
	int32 index = 0;

	FResult result;

	for (const FSlot& Slot : *SlotMap.Find(ItemType)) {
		if (Slot.ItemID == ItemID)
		{
			if (Slot.Amount < GetStackSize(ItemID))
			{
				result.Index = index;
				result.IsFindItem = true;
				return result;
			}
		}
		index++;
	}

	result.Index = -1;
	result.IsFindItem = false;

	return result;
}

FResult UInventoryComponent::CheckSlotEmpty()
{
	int32 index = 0;

	FResult result;

	for (const FSlot& Slot : *SlotMap.Find(ItemType)) {
		if (Slot.Amount == 0)
		{
			result.Index = index;
			result.IsFindItem = true;
			return result;
		}
		index++;
	}

	result.Index = -1;
	result.IsFindItem = false;

	return result;
}

int32 UInventoryComponent::GetStackSize(int32 ItemID)
{
	UBaseGameInstance* MyGameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
	if (MyGameInstance)
	{
		TWeakPtr<FItemData> ItemData = MyGameInstance->GetDatabaseMap<FItemData>(E_ManagerType::E_ItemDatabaseManager, ItemID);
		if (ItemData.IsValid())
			return ItemData.Pin()->ItemStackSize;
	}
	return -1;
}

void UInventoryComponent::IncreaseSlotStack(int32 Index, int32 Amount)
{
	TArray<FSlot>& ArrayRef = SlotMap[ItemType];
	ArrayRef[Index].Amount = ArrayRef[Index].Amount + Amount;
}

void UInventoryComponent::AddToNewSlot(int32 ItemID, int32 ItemAmount, FSpawnItemType Type)
{
	FResult result;
	result = CheckSlotEmpty();

	TArray<FSlot>& ArrayRef = SlotMap[ItemType];
	ArrayRef[result.Index].ItemID = ItemID;
	ArrayRef[result.Index].Amount = ItemAmount;
	ArrayRef[result.Index].Type = Type;
}

void UInventoryComponent::ChangeSlot(int32 BeforeIndex, int32 TargetIndex, UInventoryComponent* BeforeInvenCom)
{
	TArray<FSlot>& ArrayRef = SlotMap[ItemType];
	LocalSlot = BeforeInvenCom->GetSlot(BeforeIndex);
	if (TargetIndex >= 0)
	{
		if (LocalSlot.ItemID != ArrayRef[TargetIndex].ItemID)
		{
			BeforeInvenCom->SetSlot(BeforeIndex, ArrayRef[TargetIndex]);
			ArrayRef[TargetIndex] = LocalSlot;

		}
		else {
			BeforeInvenCom->SetSlot(BeforeIndex, ArrayRef[TargetIndex]);
			ArrayRef[TargetIndex] = LocalSlot;
		}
	}

	OnInventoryUpdated.Broadcast();
}
