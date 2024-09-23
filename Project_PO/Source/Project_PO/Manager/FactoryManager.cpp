// Fill out your copyright notice in the Description page of Project Settings.


#include "FactoryManager.h"
#include "../Actor/Item/BaseItemActor.h"
#include "../Actor/Item/DropItemActor.h"
#include "../Actor/Item/Equip/EquipItemActor.h"
#include "../Actor/Item/Equip/Weapon/Pistol/BasePistolWeaponActor.h"
#include "../Actor/Item/Equip/Weapon/Rifle/BaseRifleWeaponActor.h"
#include "../Actor/Item/Equip/Weapon/Shotgun/BaseShotgunWeaponActor.h"
#include "../Character/Enemy/EnemyCharacter.h"
#include "../Character/Enemy/GolemBossEnemyCharacter.h"
#include "../Character/Enemy/MummyNormalEnemyCharacter.h"


ABaseItemActor* UFactoryManager::EquipFactory(UWorld* World, FSpawnItemType const& Type, FTransform const& Transform, const FActorSpawnParameters& SpawnParameters)
{
	if (!World)
		return nullptr;

	ABaseItemActor* Item = nullptr;

	switch (Type.EquipType)
	{
	case E_EquipType::E_Weapon:
		Item = WeaponFactory(World, Type, Transform, SpawnParameters);
		break;
	case E_EquipType::E_Hat:
		break;
	case E_EquipType::E_Shoes:
		break;
	case E_EquipType::E_Chest:
		break;
	case E_EquipType::E_Gloves:
		break;
	case E_EquipType::E_None:
		break;
	default:
		break;
	}
	return Item;
}

ABaseItemActor* UFactoryManager::WeaponFactory(UWorld* World, FSpawnItemType const& Type, FTransform const& Transform, const FActorSpawnParameters& SpawnParameters)
{
	if (!World)
		return nullptr;

	ABaseItemActor* Item = nullptr;

	switch (Type.WeaponType)
	{
	case E_WeaponType::E_Pistol:
		Item = World->SpawnActor<ABasePistolWeaponActor>(ABasePistolWeaponActor::StaticClass(), Transform, SpawnParameters);
		break;
	case E_WeaponType::E_Rifle:
		Item = World->SpawnActor<ABaseRifleWeaponActor>(ABaseRifleWeaponActor::StaticClass(), Transform, SpawnParameters);
		break;
	case E_WeaponType::E_Shotgun:
		Item = World->SpawnActor<ABaseShotgunWeaponActor>(ABaseShotgunWeaponActor::StaticClass(), Transform, SpawnParameters);
		break;
	case E_WeaponType::E_None:
		break;
	default:
		break;
	}

	return Item;
}

AEnemyCharacter* UFactoryManager::MonsterFactory(UWorld* World, E_MonsterType const& Type, FTransform const& Transform, const FActorSpawnParameters& SpawnParameters)
{
	if (!World)
		return nullptr;

	AEnemyCharacter* Character = nullptr;

	switch (Type)
	{
	case E_MonsterType::E_Mummy:
		Character = World->SpawnActor<AMummyNormalEnemyCharacter>(AMummyNormalEnemyCharacter::StaticClass(), Transform, SpawnParameters);
		break;
	case E_MonsterType::E_Golem:
		Character = World->SpawnActor<AGolemBossEnemyCharacter>(AGolemBossEnemyCharacter::StaticClass(), Transform, SpawnParameters);
		break;
	}
	return Character;
}

ABaseItemActor* UFactoryManager::ItemFactory(UWorld* World, FSpawnItemType const& Type, FTransform const& Transform, const FActorSpawnParameters& SpawnParameters)
{
	if (!World)
		return nullptr;

	ABaseItemActor* Item = nullptr;

	switch (Type.ItemType)
	{
	case E_ItemType::E_Equip:
		Item = EquipFactory(World, Type, Transform);
		break;
	case E_ItemType::E_Cunsumable:
		//Item = GetWorld()->SpawnActor<>
		break;
	case E_ItemType::E_Etc:
		//Item = GetWorld()->SpawnActor<>
		break;
	case E_ItemType::E_Drop:
		Item = World->SpawnActor<ADropItemActor>(ADropItemActor::StaticClass(),Transform, SpawnParameters);
		break;
	}
	return Item;
}
