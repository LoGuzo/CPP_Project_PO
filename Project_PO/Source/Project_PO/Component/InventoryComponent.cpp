// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "EquipComponent.h"
#include "InteractionComponent.h"
#include "PotionQuickSlotComponent.h"
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
		result = FindSlot(ItemID, Type.ItemType);
		if (result.IsFindItem)
		{
			IncreaseSlotStack(result.Index, ItemAmount, Type.ItemType);
			AmountLeft--;
		}
		else
		{
			result = CheckSlotEmpty(Type.ItemType);
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
	if (QuickSlotComponent)
		QuickSlotComponent->OnQuickSlotUpdated.Broadcast();
}

void UInventoryComponent::DropItem(int32 TargetIndex, FSpawnItemType Type)
{
	TArray<FSlot>& ArrayRef = SlotMap[Type.ItemType];
	ArrayRef[TargetIndex] = FSlot();

	OnInventoryUpdated.Broadcast();
}

FResult UInventoryComponent::FindSlot(int32 ItemID, E_ItemType Type)
{
	int32 index = 0;

	FResult Result;

	for (const FSlot& Slot : *SlotMap.Find(Type)) {
		if (Slot.ItemID == ItemID)
		{
			if (Slot.Amount < GetStackSize(ItemID))
			{
				Result.Index = index;
				Result.IsFindItem = true;
				return Result;
			}
		}
		index++;
	}

	Result.Index = -1;
	Result.IsFindItem = false;

	return Result;
}

FResult UInventoryComponent::CheckSlotEmpty(E_ItemType Type)
{
	int32 index = 0;

	FResult Result;

	for (const FSlot& Slot : *SlotMap.Find(Type)) {
		if (Slot.Amount == 0)
		{
			Result.Index = index;
			Result.IsFindItem = true;
			return Result;
		}
		index++;
	}

	Result.Index = -1;
	Result.IsFindItem = false;

	return Result;
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

void UInventoryComponent::IncreaseSlotStack(int32 Index, int32 Amount, E_ItemType Type)
{
	TArray<FSlot>& ArrayRef = SlotMap[Type];
	ArrayRef[Index].Amount = ArrayRef[Index].Amount + Amount;
}

void UInventoryComponent::AddToNewSlot(int32 ItemID, int32 ItemAmount, FSpawnItemType Type)
{
	FResult Result;
	Result = CheckSlotEmpty(Type.ItemType);

	TArray<FSlot>& ArrayRef = SlotMap[Type.ItemType];
	ArrayRef[Result.Index].ItemID = ItemID;
	ArrayRef[Result.Index].Amount = ItemAmount;
	ArrayRef[Result.Index].Type = Type;
}

void UInventoryComponent::CheckSlotAmount(int32 Index, E_ItemType Type)
{
	TArray<FSlot>& ArrayRef = SlotMap[Type];
	ArrayRef[Index].Amount -= 1;
	if (ArrayRef[Index].Amount == 0)
		DropItem(Index, Type);
}

void UInventoryComponent::ChangeSlot(int32 BeforeIndex, int32 TargetIndex, UInventoryComponent* BeforeInvenCom)
{
	TArray<FSlot>& ArrayRef = SlotMap[ItemType];
	LocalSlot = BeforeInvenCom->GetSlot(BeforeIndex, ItemType);
	if (TargetIndex >= 0)
	{
		if (LocalSlot.ItemID != ArrayRef[TargetIndex].ItemID)
		{
			BeforeInvenCom->SetSlot(BeforeIndex, ArrayRef[TargetIndex], ItemType);
			ArrayRef[TargetIndex] = LocalSlot;

		}
		else {
			BeforeInvenCom->SetSlot(BeforeIndex, ArrayRef[TargetIndex], ItemType);
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
					DropItem(Index, Type);
					AddItem(EquipID, 1, Type);

					OwnPlayer->SetEquip(ItemID);
				}
			}
			else
			{
				FSpawnItemType Type = FSpawnItemType(E_ItemType::E_Equip);
				DropItem(Index, Type);
				OwnPlayer->SetEquip(ItemID);
			}
		}
	}
}

void UInventoryComponent::UseItem(int32 Index, E_ItemType Type)
{
	switch (Type)
	{
	case E_ItemType::E_Cunsumable:
		UseCunsumItem(Index, Type);
		break;
	case E_ItemType::E_Etc:
		UseEtcItem(Index, Type);
		break;
	default:
		break;
	}
}

void UInventoryComponent::UseCunsumItem(int32 Index, E_ItemType Type)
{
	CheckSlotAmount(Index, Type);
	if (QuickSlotComponent)
		QuickSlotComponent->OnQuickSlotUpdated.Broadcast();
}

void UInventoryComponent::UseEtcItem(int32 Index, E_ItemType Type)
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
					FSlot NowSlot = GetSlot(Index, Type);
					AInstallItemActor* InstallItem = Cast<AInstallItemActor>(ObjectPoolManager->GetItem(GetWorld(), NowSlot.Type));
					if (InstallItem)
					{
						InstallItem->SetItem(NowSlot.ItemID);
						InstallItem->SetOwner(OwnPlayer);
						InteractionComponent->SetInstallItem(InstallItem);
					}
				}
			}
		}
	}
}

void UInventoryComponent::CheckUseItemAmount(int32 ItemID, E_ItemType Type)
{
	FResult Result;

	Result = FindSlot(ItemID, Type);
	if (Result.IsFindItem)
		CheckSlotAmount(Result.Index, Type);
}

void UInventoryComponent::RegisterQuickSlot(int32 Index)
{
	if (QuickSlotComponent)
		QuickSlotComponent->RegisterQuickSlot(Index, this);
}

int32 UInventoryComponent::CheckFullItemAmount(int32 ItemID)
{
	int32 index = 0;
	int32 Amount = 0;

	for (const FSlot& Slot : *SlotMap.Find(E_ItemType::E_Cunsumable)) {
		if (Slot.ItemID == ItemID)
			Amount += Slot.Amount;
		index++;
	}

	return Amount;
}