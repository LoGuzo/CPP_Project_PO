// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseShotgunWeaponActor.h"
#include "../../../../../Widget/Etc/CrosshairEtcWidget.h"

ABaseShotgunWeaponActor::ABaseShotgunWeaponActor()
{
	WeaponType = E_WeaponType::E_Shotgun;

	static ConstructorHelpers::FClassFinder<UCrosshairEtcWidget> Crosshair(TEXT("/Game/ThirdPerson/Blueprints/Widget/Etc/BP_ShotgunCrosshair.BP_ShotgunCrosshair_C"));
	if (Crosshair.Succeeded())
		CrosshairWidget = Crosshair.Class;
}

void ABaseShotgunWeaponActor::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("Shotgun"));
}