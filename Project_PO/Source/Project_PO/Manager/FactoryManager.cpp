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


ABaseItemActor* UFactoryManager::EquipFactory(E_EquipType EquipType, E_WeaponType WeaponType)
{
	ABaseItemActor* Item = nullptr;
	switch (EquipType)
	{
	case E_EquipType::E_Weapon:
		Item = WeaponFactory(WeaponType);
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

ABaseItemActor* UFactoryManager::WeaponFactory(E_WeaponType WeaponType)
{
	ABaseItemActor* Item = nullptr;

	switch (WeaponType)
	{
	case E_WeaponType::E_Pistol:
		Item = GetWorld()->SpawnActor<ABasePistolWeaponActor>(ABasePistolWeaponActor::StaticClass());
		break;
	case E_WeaponType::E_Rifle:
		Item = GetWorld()->SpawnActor<ABaseRifleWeaponActor>(ABaseRifleWeaponActor::StaticClass());
		break;
	case E_WeaponType::E_Shotgun:
		Item = GetWorld()->SpawnActor<ABaseShotgunWeaponActor>(ABaseShotgunWeaponActor::StaticClass());
		break;
	case E_WeaponType::E_None:
		break;
	default:
		break;
	}

	return Item;
}

AEnemyCharacter* UFactoryManager::MonsterFactory(E_MonsterType Type)
{
	AEnemyCharacter* Character = nullptr;
	switch (Type)
	{
	case E_MonsterType::E_Mummy:
		Character = GetWorld()->SpawnActor<AMummyNormalEnemyCharacter>(AMummyNormalEnemyCharacter::StaticClass());
		break;
	case E_MonsterType::E_Golem:
		Character = GetWorld()->SpawnActor<AGolemBossEnemyCharacter>(AGolemBossEnemyCharacter::StaticClass());
		break;
	}
	return Character;
}

ABaseItemActor* UFactoryManager::ItemFactory(E_ItemType Type, E_EquipType EquipType, E_WeaponType WeaponType)
{
	ABaseItemActor* Item = nullptr;
	switch (Type)
	{
	case E_ItemType::E_Equip:
		EquipFactory(EquipType, WeaponType);
		break;
	case E_ItemType::E_Cunsumable:
		//Item = GetWorld()->SpawnActor<>
		break;
	case E_ItemType::E_Etc:
		//Item = GetWorld()->SpawnActor<>
		break;
	case E_ItemType::E_Drop:
		Item = GetWorld()->SpawnActor<ADropItemActor>(ADropItemActor::StaticClass());
		break;
	}
	return Item;
}
