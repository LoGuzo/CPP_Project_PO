// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePistolWeaponActor.h"
#include "../../../../../Widget/Etc/CrosshairEtcWidget.h"

ABasePistolWeaponActor::ABasePistolWeaponActor()
{
	WeaponType = E_WeaponType::E_Rifle;

	static ConstructorHelpers::FClassFinder<UCrosshairEtcWidget> Crosshair(TEXT("/Game/ThirdPerson/Blueprints/Widget/Etc/BP_NormalCrosshair.BP_NormalCrosshair_C"));
	if (Crosshair.Succeeded())
		CrosshairWidget = Crosshair.Class;
}

void ABasePistolWeaponActor::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("Pistol"));
}