// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../Actor/Item/Equip/Weapon/BaseWeaponActor.h"
#include "../Actor/Item/Equip/Weapon/Pistol/BasePistolWeaponActor.h"
#include "../Actor/Item/Equip/Weapon/Rifle/BaseRifleWeaponActor.h"
#include "../Actor/Item/Equip/Weapon/Shotgun/BaseShotgunWeaponActor.h"
#include "../Character/Player/PlayerCharacter.h"
#include "../Manager/BaseGameInstance.h"
#include "../Manager/WidgetManager.h"
#include "../Widget/Etc/CrosshairEtcWidget.h"

// Sets default values for this component's properties
UEquipComponent::UEquipComponent()
	: CurrentWeapon(nullptr)
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
	FName SocketName;

	if (CurrentWeapon)
		CurrentWeapon->Destroy();

	switch (WeaponType)
	{
	case E_WeaponType::E_Pistol:
		CurrentWeapon = GetWorld()->SpawnActor<ABasePistolWeaponActor>(ABasePistolWeaponActor::StaticClass());
		SocketName = FName(TEXT("pistol_socket"));
		break;
	case E_WeaponType::E_Rifle:
		CurrentWeapon = GetWorld()->SpawnActor<ABaseRifleWeaponActor>(ABaseRifleWeaponActor::StaticClass());
		SocketName = FName(TEXT("rifle_socket"));
		break;
	case E_WeaponType::E_Shotgun:
		CurrentWeapon = GetWorld()->SpawnActor<ABaseShotgunWeaponActor>(ABaseShotgunWeaponActor::StaticClass());
		SocketName = FName(TEXT("shotgun_socket"));
		break;
	default:
		break;
	}

	if (OwnPlayer)
	{
		OwnPlayer->SetWeaponType(WeaponType);
		if (CurrentWeapon)
		{
			CurrentWeapon->SetItem(DataID);
			CurrentWeapon->SetOwner(OwnPlayer);
			CurrentWeapon->AttachToComponent(OwnPlayer->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, SocketName);
			auto MyGameInstance = Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
			if (MyGameInstance)
			{
				if (CurrentWeapon->GetCrosshairWdiget())
				{
					UWidgetManager* WidgetManager = MyGameInstance->GetManager<UWidgetManager>(E_ManagerType::E_WidgetManager);
					if (WidgetManager)
					{
						UBaseUserWidget* CrossWidget = WidgetManager->CreateAndAddWidget<UCrosshairEtcWidget>(
							GetWorld(), TEXT("CrosshairWidget"),
							CurrentWeapon->GetCrosshairWdiget()
						);
						if (CrossWidget)
							CrossWidget->SetAddRemove();
					}
				}
			}
		}
	}
}

void UEquipComponent::SetEquipment(const E_EquipType EquipType, const FItemData ItemData)
{
	EquipMap.Emplace(EquipType, ItemData);
	switch (EquipType)
	{
	case E_EquipType::E_Weapon:
		SpawnWeapon(ItemData.WeaponType, ItemData.ItemID);
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

