// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipComponent.h"
#include "../Actor/Item/Equip/Weapon/BaseWeaponActor.h"
#include "../Actor/Item/Equip/Weapon/Rifle/BaseRifleWeaponActor.h"
#include "../Actor/Item/Equip/Weapon/Shotgun/BaseShotgunWeaponActor.h"
#include "../Character/Player/PlayerCharacter.h"

// Sets default values for this component's properties
UEquipComponent::UEquipComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UEquipComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UEquipComponent::SpawnWeapon(const E_WeaponType WeaponType, const int32 DataID)
{
	ABaseWeaponActor* Weapon = nullptr;
	FName SocketName;

	switch (WeaponType)
	{
	case E_WeaponType::E_Pistol:
		
		SocketName = FName(TEXT("pistol_socket"));
		break;
	case E_WeaponType::E_Rifle:
		Weapon = GetWorld()->SpawnActor<ABaseRifleWeaponActor>(ABaseRifleWeaponActor::StaticClass());
		SocketName = FName(TEXT("rifle_socket"));
		break;
	case E_WeaponType::E_Shotgun:
		Weapon = GetWorld()->SpawnActor<ABaseShotgunWeaponActor>(ABaseShotgunWeaponActor::StaticClass());
		SocketName = FName(TEXT("shotgun_socket"));
		break;
	default:
		break;
	}
	if (OwnPlayer)
	{
		OwnPlayer->SetWeaponType(WeaponType);
		if (Weapon)
		{
			Weapon->SetItem(DataID);
			Weapon->AttachToComponent(OwnPlayer->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, SocketName);
		}
	}
}

void UEquipComponent::SetEquipment(const E_EquipType EquipType, const int32 DataID)
{
	switch (EquipType)
	{
	case E_EquipType::E_Weapon:
		SpawnWeapon(E_WeaponType::E_Shotgun, DataID);
		break;
	case E_EquipType::E_Hat:
		break;
	case E_EquipType::E_Shoes:
		break;
	case E_EquipType::E_Chest:
		break;
	case E_EquipType::E_Gloves:
		break;
	default:
		break;
	}
}

