// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPoolManager.h"
#include "FactoryManager.h"
#include "SingletonManager.h"
#include "../Actor/Item/BaseItemActor.h"
#include "../Character/Enemy/EnemyCharacter.h"
#include "../Component/ItemComponent/EquipItemComponent.h"

AEnemyCharacter* UObjectPoolManager::GetMonster(UWorld* World, E_MonsterType Type, FVector Location, FRotator Rotation)
{
	if (!World)
		return nullptr;

	for (int32 i = 0; i < AvailableMonsters.Num(); i++)
	{
		if (AvailableMonsters[i] && AvailableMonsters[i]->GetMonsterType() == Type)
		{
			AEnemyCharacter* Monster = AvailableMonsters[i];
			Monster->SetState(true);
			AvailableMonsters.Remove(Monster);
			InUseMonsters.Add(Monster);
			return Monster;
		}
	}
	AEnemyCharacter* NewMonster = SingletonManager::GetInstance<UFactoryManager>()->MonsterFactory(World, Type, Location, Rotation);
	InUseMonsters.Add(NewMonster);

	return NewMonster;
}

void UObjectPoolManager::ReleaseMonster(AEnemyCharacter* Monster)
{
	if (Monster)
	{
		Monster->SetState(false);
		AvailableMonsters.Add(Monster);
		InUseMonsters.Remove(Monster);
	}
}

ABaseItemActor* UObjectPoolManager::GetItem(UWorld* World, E_ItemType Type, FVector Location, FRotator Rotation , E_EquipType EquipType, E_WeaponType WeaponType)
{
	if (!World)
		return nullptr;

	for (int32 i = 0; i < AvailableItems.Num(); i++)
	{
		if (AvailableItems[i])
		{
			ABaseItemActor* Item = AvailableItems[i];

			if (Type == E_ItemType::E_Equip)
			{
				UEquipItemComponent* ItemComponent = Item->GetItemComponent<UEquipItemComponent>();
				if (ItemComponent->GetEquipType() != EquipType)
					continue;

				if (EquipType == E_EquipType::E_Weapon && ItemComponent->GetWeaponType() != WeaponType)
					continue;
			}

			Item->SetState(true);
			AvailableItems.Remove(Item);
			InUseItems.Add(Item);
			return Item;
		}
	}

	ABaseItemActor* Item = SingletonManager::GetInstance<UFactoryManager>()->ItemFactory(World, Type, Location, Rotation, EquipType, WeaponType);
	InUseItems.Add(Item);
	return Item;
}

void UObjectPoolManager::ReleaseItem(ABaseItemActor* Item)
{
	if (Item)
	{
		Item->SetState(false);
		AvailableItems.Add(Item);
		InUseItems.Remove(Item);
	}
}
