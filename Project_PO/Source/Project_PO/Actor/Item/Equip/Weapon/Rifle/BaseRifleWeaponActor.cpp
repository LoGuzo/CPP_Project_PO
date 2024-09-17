// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseRifleWeaponActor.h"
#include "../../../../../Widget/Etc/CrosshairEtcWidget.h"

ABaseRifleWeaponActor::ABaseRifleWeaponActor()
{
	WeaponType = E_WeaponType::E_Rifle;

	static ConstructorHelpers::FClassFinder<UCrosshairEtcWidget> Crosshair(TEXT("/Game/ThirdPerson/Blueprints/Widget/Etc/BP_NormalCrosshair.BP_NormalCrosshair_C"));
	if (Crosshair.Succeeded())
		CrosshairWidget = Crosshair.Class;

}

void ABaseRifleWeaponActor::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("Rifle"));
}
