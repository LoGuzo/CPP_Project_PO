// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "EquipComponent.h"
#include "InteractionComponent.h"
#include "ItemComponent/EquipItemComponent.h"
#include "../Actor/Item/Equip/Weapon/BaseWeaponActor.h"
#include "../Actor/Item/InstallItemActor.h"
#include "../Character/Player/PlayerCharacter.h"
#include "../Manager/BaseGameInstance.h"
#include "../Manager/ObjectPoolManager.h"

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
	SlotMap.Emplace(E_ItemType::E_Equip, Slots);
	Slots[0].ItemID = 1003;
	Slots[0].Amount = 2;
	Slots[0].Type = FSpawnItemType(E_ItemType::E_Cunsumable, E_EquipType::E_Registerable);
	SlotMap.Emplace(E_ItemType::E_Cunsumable, Slots);
	Slots[0].ItemID = 1005;
	Slots[0].Amount = 1;
	Slots[0].Type = FSpawnItemType(E_ItemType::E_Etc);
	Slots[1].ItemID = 1006;
	Slots[1].Amount = 1;
	Slots[1].Type = FSpawnItemType(E_ItemType::E_Etc, E_EquipType::E_Installable);
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

	OnInventoryUpdated.Broadcast();
}

void UInventoryComponent::DropItem(int32 TargetIndex)
{
	TArray<FSlot>& ArrayRef = SlotMap[ItemType];
	ArrayRef[TargetIndex] = FSlot();

	OnInventoryUpdated.Broadcast();
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
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		TWeakPtr<FItemData> ItemData = GameInstance->GetDatabaseMap<FItemData>(E_ManagerType::E_ItemDatabaseManager, ItemID);
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

	ItemType = Type.ItemType;

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

void UInventoryComponent::ChangeEquip(int32 Index, int32 ItemID)
{
	if (OwnPlayer)
	{
		UEquipComponent* EquipComponent = OwnPlayer->GetEquipComponent();
		if (EquipComponent)
		{
			ABaseItemActor* Weapon = EquipComponent->GetCurrentWeapon();
			if (Weapon)
			{
				UEquipItemComponent* EquipItemComponent = Weapon->GetItemComponent<UEquipItemComponent>();
				if (EquipItemComponent)
				{
					int32 EquipID = EquipItemComponent->GetID();
					FSpawnItemType Type = EquipItemComponent->GetItemType();
					DropItem(Index);
					AddItem(EquipID, 1, Type);

					OwnPlayer->SetEquip(ItemID);
				}
			}
			else
			{
				DropItem(Index);
				OwnPlayer->SetEquip(ItemID);
			}
		}
	}
}

void UInventoryComponent::UseItem(int32 Index)
{
	switch (ItemType)
	{
	case E_ItemType::E_Cunsumable:
		UseCunsumItem(Index);
		break;
	case E_ItemType::E_Etc:
		UseEtcItem(Index);
		break;
	default:
		break;
	}
}

void UInventoryComponent::UseCunsumItem(int32 Index)
{

}

void UInventoryComponent::UseEtcItem(int32 Index)
{
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		if (OwnPlayer)
		{
			UInteractionComponent* InteractionComponent = OwnPlayer->GetInteractionComponent();
			if (InteractionComponent)
			{
				UObjectPoolManager* ObjectPoolManager = GameInstance->GetManager<UObjectPoolManager>(E_ManagerType::E_ObjectPoolManager);
				if (ObjectPoolManager)
				{
					FSlot NowSlot = GetSlot(Index);
					AInstallItemActor* InstallItem = Cast<AInstallItemActor>(ObjectPoolManager->GetItem(GetWorld(), NowSlot.Type));
					if (InstallItem)
					{
						InstallItem->SetItem(NowSlot.ItemID);
						InteractionComponent->SetInstallItem(InstallItem);
					}
				}
			}
		}
	}
}

void UInventoryComponent::RegisterQuickSlot(int32 Index, int32 ItemID)
{
}