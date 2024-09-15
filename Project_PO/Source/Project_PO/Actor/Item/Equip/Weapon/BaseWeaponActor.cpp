// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWeaponActor.h"

ABaseWeaponActor::ABaseWeaponActor()
	: WeaponType(E_WeaponType::E_None)
{
	EquipType = E_EquipType::E_Weapon;
}
