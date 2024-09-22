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


ABaseItemActor* UFactoryManager::EquipFactory(UWorld* World, E_EquipType EquipType, FVector Location, FRotator Rotation, E_WeaponType WeaponType)
{
	if (!World)
		return nullptr;

	ABaseItemActor* Item = nullptr;

	switch (EquipType)
	{
	case E_EquipType::E_Weapon:
		Item = WeaponFactory(World, WeaponType, Location, Rotation);
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

ABaseItemActor* UFactoryManager::WeaponFactory(UWorld* World, E_WeaponType WeaponType, FVector Location, FRotator Rotation)
{
	if (!World)
		return nullptr;

	ABaseItemActor* Item = nullptr;

	switch (WeaponType)
	{
	case E_WeaponType::E_Pistol:
		Item = World->SpawnActor<ABasePistolWeaponActor>(ABasePistolWeaponActor::StaticClass(), Location, Rotation);
		break;
	case E_WeaponType::E_Rifle:
		Item = World->SpawnActor<ABaseRifleWeaponActor>(ABaseRifleWeaponActor::StaticClass(), Location, Rotation);
		break;
	case E_WeaponType::E_Shotgun:
		Item = World->SpawnActor<ABaseShotgunWeaponActor>(ABaseShotgunWeaponActor::StaticClass(), Location, Rotation);
		break;
	case E_WeaponType::E_None:
		break;
	default:
		break;
	}

	return Item;
}

AEnemyCharacter* UFactoryManager::MonsterFactory(UWorld* World, E_MonsterType Type, FVector Location, FRotator Rotation)
{
	if (!World)
		return nullptr;

	AEnemyCharacter* Character = nullptr;

	switch (Type)
	{
	case E_MonsterType::E_Mummy:
		Character = World->SpawnActor<AMummyNormalEnemyCharacter>(AMummyNormalEnemyCharacter::StaticClass(), Location, Rotation);
		break;
	case E_MonsterType::E_Golem:
		Character = World->SpawnActor<AGolemBossEnemyCharacter>(AGolemBossEnemyCharacter::StaticClass(), Location, Rotation);
		break;
	}
	return Character;
}

ABaseItemActor* UFactoryManager::ItemFactory(UWorld* World, E_ItemType Type, FVector Location, FRotator Rotation, E_EquipType EquipType, E_WeaponType WeaponType)
{
	if (!World)
		return nullptr;

	ABaseItemActor* Item = nullptr;

	switch (Type)
	{
	case E_ItemType::E_Equip:
		EquipFactory(World, EquipType, Location, Rotation, WeaponType);
		break;
	case E_ItemType::E_Cunsumable:
		//Item = GetWorld()->SpawnActor<>
		break;
	case E_ItemType::E_Etc:
		//Item = GetWorld()->SpawnActor<>
		break;
	case E_ItemType::E_Drop:
		Item = World->SpawnActor<ADropItemActor>(ADropItemActor::StaticClass(), Location, Rotation);
		break;
	}
	return Item;
}
