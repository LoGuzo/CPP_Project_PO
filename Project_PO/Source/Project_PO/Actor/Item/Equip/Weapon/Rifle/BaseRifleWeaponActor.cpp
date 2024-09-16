// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseRifleWeaponActor.h"

ABaseRifleWeaponActor::ABaseRifleWeaponActor()
{
	WeaponType = E_WeaponType::E_Rifle;

	RootComponent = GetSkeletalMesh();
}

void ABaseRifleWeaponActor::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("Chk"));
}
