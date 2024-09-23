// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPoolManager.h"
#include "FactoryManager.h"
#include "SingletonManager.h"
#include "../Actor/Item/BaseItemActor.h"
#include "../Character/Enemy/EnemyCharacter.h"
#include "../Component/ItemComponent/EquipItemComponent.h"

AEnemyCharacter* UObjectPoolManager::GetMonster(UWorld* World, E_MonsterType const& Type, FTransform const& Transform, const FActorSpawnParameters& SpawnParameters)
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
	AEnemyCharacter* NewMonster = SingletonManager::GetInstance<UFactoryManager>()->MonsterFactory(World, Type, Transform, SpawnParameters);
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

ABaseItemActor* UObjectPoolManager::GetItem(UWorld* World, FSpawnItemType const& Type, FTransform const& Transform, const FActorSpawnParameters& SpawnParameters)
{
	if (!World)
		return nullptr;

	for (int32 i = 0; i < AvailableItems.Num(); i++)
	{
		if (AvailableItems[i])
		{
			ABaseItemActor* Item = AvailableItems[i];

			if (Type.ItemType == E_ItemType::E_Equip)
			{
				UEquipItemComponent* ItemComponent = Item->GetItemComponent<UEquipItemComponent>();
				if (ItemComponent->GetEquipType() != Type.EquipType)
					continue;

				if (Type.EquipType == E_EquipType::E_Weapon && ItemComponent->GetWeaponType() != Type.WeaponType)
					continue;
			}

			Item->SetState(true);
			AvailableItems.Remove(Item);
			InUseItems.Add(Item);
			return Item;
		}
	}

	ABaseItemActor* NewItem = SingletonManager::GetInstance<UFactoryManager>()->ItemFactory(World, Type, Transform, SpawnParameters);
	InUseItems.Add(NewItem);
	return NewItem;
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
