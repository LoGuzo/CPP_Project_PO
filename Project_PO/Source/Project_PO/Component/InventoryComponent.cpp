// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "EquipComponent.h"
#include "InteractionComponent.h"
#include "ItemComponent/EquipItemComponent.h"
#include "StatComponent/StatComponent.h"
#include "QuickSlotComponent/PotionQuickSlotComponent.h"
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
	SlotMap.Emplace(E_ItemType::E_Cunsumable, Slots);
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
			IncreaseSlotStack(result.Index, 1, Type.ItemType);
			AmountLeft--;
		}
		else
		{
			result = CheckSlotEmpty(Type.ItemType);
			if (result.IsFindItem)
			{
				AddToNewSlot(ItemID, 1, Type);
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

FResult UInventoryComponent::FindItem(int32 ItemID, E_ItemType Type)
{
	int32 index = 0;
	int32 MinStackSize = GetStackSize(ItemID) + 1;
	int32 MinIndex = -1;

	FResult Result;

	for (const FSlot& Slot : *SlotMap.Find(Type)) {
		if (Slot.ItemID == ItemID)
		{
			int32 AvailableStackSpace = GetStackSize(ItemID) - Slot.Amount;

			if (AvailableStackSpace >= 0 && AvailableStackSpace < MinStackSize)
			{
				MinStackSize = AvailableStackSpace;
				MinIndex = index;
				Result.IsFindItem = true;
			}
		}
		index++;
	}

	if (MinIndex != -1) {
		Result.Index = MinIndex;
	}
	else {
		Result.Index = -1;
		Result.IsFindItem = false;
	}

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
	UE_LOG(LogTemp, Warning, TEXT("%d"), ArrayRef[Index].Amount);
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

void UInventoryComponent::UseItem(int32 Index, FSpawnItemType Type)
{
	switch (Type.ItemType)
	{
	case E_ItemType::E_Cunsumable:
		UseCunsumItem(Index, Type.ItemType);
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
	FSlot CunsumSlot = GetSlot(Index, Type);

	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		TWeakPtr<FCunsumItemData> ItemData = GameInstance->GetDatabaseMap<FCunsumItemData>(E_ManagerType::E_ItemDatabaseManager ,CunsumSlot.ItemID);
		if (ItemData.IsValid())
		{
			float RestoreAmount = ItemData.Pin()->RestoreAmount;

			if (StatComponent)
			{
				switch (ItemData.Pin()->CunsumType)
				{
				case E_CunsumableType::E_Hp:
					StatComponent->HealHp(RestoreAmount);
					break;
				case E_CunsumableType::E_Mp:
					StatComponent->HealMp(RestoreAmount);
					break;
				default:
					break;
				}
			}
		}
	}
	CheckSlotAmount(Index, Type);
	if (QuickSlotComponent)
		QuickSlotComponent->OnQuickSlotUpdated.Broadcast();
}

void UInventoryComponent::UseEtcItem(int32 Index, FSpawnItemType Type)
{
	switch (Type.EquipType)
	{
	case E_EquipType::E_Installable:
		UseInstallEtcItem(Index, Type.ItemType);
		break;
	default:
		CheckSlotAmount(Index, Type.ItemType);
		break;
	}
}

void UInventoryComponent::UseInstallEtcItem(int32 Index, E_ItemType Type)
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

	Result = FindItem(ItemID, Type);
	if (Result.IsFindItem)
		CheckSlotAmount(Result.Index, Type);
}

void UInventoryComponent::RegisterQuickSlot(int32 Index)
{
	if (QuickSlotComponent)
		QuickSlotComponent->RegisterQuickSlot(Index, this);
}

FMinResult UInventoryComponent::CheckFullItemAmount(int32 ItemID)
{
	int32 index = 0;
	int32 Amount = INT32_MAX;

	FMinResult MinSlot;

	for (const FSlot& Slot : *SlotMap.Find(E_ItemType::E_Cunsumable)) {
		if (Slot.ItemID == ItemID)
		{
			if (Slot.Amount <= Amount)
			{
				MinSlot.Index = index;
				Amount = Slot.Amount;
			}
			MinSlot.Amount += Slot.Amount;
		}
		index++;
	}

	return MinSlot;
}