// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemComponent.h"
#include "../GameMode/MyBaseGameMode.h"

// Sets default values for this component's properties
UItemComponent::UItemComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UItemComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UItemComponent::SetItem(int32 _ItemID)
{
	AMyBaseGameMode* Gamemode = Cast<AMyBaseGameMode>(GetWorld()->GetAuthGameMode());
	if (Gamemode)
	{
		TWeakPtr<FItemData> ItemData = Gamemode->GetDatabaseMap<FItemData>(E_ManagerType::E_ItemDatabaseManager, _ItemID);
		if (ItemData.IsValid())
		{
			ItemID = ItemData.Pin()->ItemID;
			ItemName = ItemData.Pin()->ItemName;
			ItemDescription = ItemData.Pin()->ItemDescription;
			ItemImage = ItemData.Pin()->ItemImage;
			ItemStackSize = ItemData.Pin()->ItemStackSize;
			ItemType = ItemData.Pin()->ItemType;
			ItemMesh = ItemData.Pin()->ItemMesh;
			EquipType = ItemData.Pin()->EquipType;
			DropChance = ItemData.Pin()->DropChance;
			WeaponType = ItemData.Pin()->WeaponType;
			AttackPower = ItemData.Pin()->AttackPower;
			DefensePower = ItemData.Pin()->DefensePower;
			RestoreAmount = ItemData.Pin()->RestoreAmount;
			Duration = ItemData.Pin()->Duration;
			Cooltime = ItemData.Pin()->Cooltime;
		}
	}
}

