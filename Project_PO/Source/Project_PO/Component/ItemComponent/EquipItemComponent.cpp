// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipItemComponent.h"
#include "../../Manager/BaseGameInstance.h"

UEquipItemComponent::UEquipItemComponent()
{
}

void UEquipItemComponent::SetItem(int32 _ID)
{
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		TWeakPtr<FEquipItemData> ItemData = GameInstance->GetDatabaseMap<FEquipItemData>(E_ManagerType::E_ItemDatabaseManager, _ID);
		if (ItemData.IsValid())
		{
			ID = ItemData.Pin()->ID;
			ItemName = ItemData.Pin()->ItemName;
			ItemDescription = ItemData.Pin()->ItemDescription;
			ItemImage = ItemData.Pin()->ItemImage;
			ItemStackSize = ItemData.Pin()->ItemStackSize;
			ItemType = ItemData.Pin()->ItemType;
			ItemMesh = ItemData.Pin()->ItemMesh;
			DropChance = ItemData.Pin()->DropChance;
			AttackPower = ItemData.Pin()->AttackPower;
			DefensePower = ItemData.Pin()->DefensePower;
			WeaponAnimInstance = ItemData.Pin()->AnimInstance;
		}
	}
}
