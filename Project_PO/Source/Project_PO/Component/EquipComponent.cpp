// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipComponent.h"
#include "../Actor/Item/Equip/Weapon/BaseWeaponActor.h"
#include "../Actor/Item/Equip/Weapon/Pistol/BasePistolWeaponActor.h"
#include "../Actor/Item/Equip/Weapon/Rifle/BaseRifleWeaponActor.h"
#include "../Actor/Item/Equip/Weapon/Shotgun/BaseShotgunWeaponActor.h"
#include "../Character/Player/PlayerCharacter.h"
#include "../Manager/BaseGameInstance.h"
#include "../Manager/ObjectPoolManager.h"
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
	if (OwnPlayer)
	{
		OwnPlayer->SetWeaponType(WeaponType);
		UBaseGameInstance* MyGameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
		if (MyGameInstance)
		{
			UObjectPoolManager* ObjectPoolManager = MyGameInstance->GetManager<UObjectPoolManager>(E_ManagerType::E_ObjectPoolManager);

			if (!ObjectPoolManager)
				return;

			if (CurrentWeapon)
			{
				CurrentWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
				ObjectPoolManager->ReleaseItem(CurrentWeapon);
				CurrentWeapon = nullptr;
			}

			FSpawnItemType Type = FSpawnItemType(E_ItemType::E_Equip, E_EquipType::E_Weapon, WeaponType);
			FActorSpawnParameters SpawnParmeters;
			SpawnParmeters.Name = *FString::FromInt(DataID);
			SpawnParmeters.Owner = OwnPlayer;

			FName SocketName;

			switch (WeaponType)
			{
			case E_WeaponType::E_Pistol:
				SocketName = FName(TEXT("pistol_socket"));
				break;
			case E_WeaponType::E_Rifle:
				SocketName = FName(TEXT("rifle_socket"));
				break;
			case E_WeaponType::E_Shotgun:
				SocketName = FName(TEXT("shotgun_socket"));
				break;
			default:
				break;
			}

			CurrentWeapon = Cast<ABaseWeaponActor>(ObjectPoolManager->GetItem(GetWorld(), Type, FTransform(), SpawnParmeters));
			if (CurrentWeapon)
			{
				CurrentWeapon->SetItem(DataID);
				CurrentWeapon->SetOwner(OwnPlayer);
				CurrentWeapon->AttachToComponent(OwnPlayer->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, SocketName);

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

void UEquipComponent::SetEquipment(const E_EquipType EquipType, const FEquipItemData ItemData)
{
	if (ItemData.ItemID == -1)
		return;

	EquipMap.Emplace(EquipType, ItemData);

	switch (EquipType)
	{
	case E_EquipType::E_Weapon:
		SpawnWeapon(ItemData.WeaponType, ItemData.ItemID);
		break;
	case E_EquipType::E_Hat:
	case E_EquipType::E_Shoes:
	case E_EquipType::E_Chest:
	case E_EquipType::E_Gloves:
		break;
	default:
		break;
	}
}

